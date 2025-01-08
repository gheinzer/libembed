#include <libembed/arch/arm/stm32/gpio.h>
#include <libembed/hal/gpio.h>
#include <libembed/util/coroutines.h>
#include <libembed/arch/ident.h>
#include <libembed/exceptions.h>

#if STM32F412xx

using namespace embed::arch::arm::stm32;

// *** Analog input pins ***
gpio::AnalogInput_Pin stm32f412::gpio::PA0_ADC1_0 =  { .gpio = &(gpio::PA0), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA1_ADC1_1 =  { .gpio = &(gpio::PA1), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA2_ADC1_2 =  { .gpio = &(gpio::PA2), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA3_ADC1_3 =  { .gpio = &(gpio::PA3), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA4_ADC1_4 =  { .gpio = &(gpio::PA4), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA5_ADC1_5 =  { .gpio = &(gpio::PA5), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA6_ADC1_6 =  { .gpio = &(gpio::PA6), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PA7_ADC1_7 =  { .gpio = &(gpio::PA7), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PB0_ADC1_8 =  { .gpio = &(gpio::PB0), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PB1_ADC1_9 =  { .gpio = &(gpio::PB1), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC0_ADC1_10 = { .gpio = &(gpio::PC0), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC1_ADC1_11 = { .gpio = &(gpio::PC1), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC2_ADC1_12 = { .gpio = &(gpio::PC2), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC3_ADC1_13 = { .gpio = &(gpio::PC3), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC4_ADC1_14 = { .gpio = &(gpio::PC4), .channel = 0 };
gpio::AnalogInput_Pin stm32f412::gpio::PC5_ADC1_15 = { .gpio = &(gpio::PC5), .channel = 0 };

// *** Analog-to-Digital-Converter ***
static volatile uint32_t results[16] = { 0 };
static volatile uint8_t usedRanks = 0;

/**
 * @brief Adds a new channel to the ADC.
 * 
 * @param channel Channel number to add.
 */
static void adc_addChannel(gpio::AnalogInput_Pin& pin) {
    if(usedRanks >= 16) throw std::runtime_error("ADC fully occupied.");
    
    uint8_t rank = usedRanks;
    usedRanks++;

    uint8_t sqr_registerIndex = rank / 6;
    uint8_t sqr_registerShift = (rank % 6) * 5;
    volatile uint32_t* sqr_registerPtr;

    switch(sqr_registerIndex) {
        case 0: sqr_registerPtr = &(ADC1->SQR3); break;
        case 1: sqr_registerPtr = &(ADC1->SQR2); break;
        case 2: sqr_registerPtr = &(ADC1->SQR1); break;
    }

    uint8_t smpr_registerIndex = pin.channel / 9;
    uint8_t smpr_registerShift = (pin.channel % 9) * 3;
    volatile uint32_t* smpr_registerPtr;

    switch(smpr_registerIndex) {
        case 0: smpr_registerPtr = &(ADC1->SMPR2); break;
        case 1: smpr_registerPtr = &(ADC1->SMPR1); break;
    }

    // Set the channel index in the SQR register
    MODIFY_REG(*sqr_registerPtr, ((~pin.channel) & 0b11111) << sqr_registerShift, pin.channel << sqr_registerShift);

    // Configure the channel's sample time
    MODIFY_REG(*smpr_registerPtr, ((~0b110) & 0b111) << smpr_registerShift, 0b110 << smpr_registerShift);

    pin.gpio->setAnalog();

    pin.resultVariable = &(results[rank]);
}

/**
 * @brief Initializes the ADC and the DMA.
 * 
 * @param forceInit Whether to force re-initialization of the ADC and the DMA.
 */
static void init_adc_(bool forceInit = false) {
    static bool isInitialized = false;
    if(isInitialized && !forceInit) return;

    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    // *** DMA Configuration ***
    CLEAR_BIT(DMA2_Stream0->CR, DMA_SxCR_EN); // Make sure to disable the DMA stream
    // Channel 0 is selected by default
    // Peripheral-to-memory is default

    // Enable circular mode
    SET_BIT(DMA2_Stream0->CR, DMA_SxCR_CIRC);
    // Enable MINC
    SET_BIT(DMA2_Stream0->CR, DMA_SxCR_MINC);
    // Disable PINC
    CLEAR_BIT(DMA2_Stream0->CR, DMA_SxCR_PINC);

    // Data Size = Word (32-Bit)
    SET_BIT(DMA2_Stream0->CR, DMA_SxCR_PSIZE_1); // Peripheral data size
    SET_BIT(DMA2_Stream0->CR, DMA_SxCR_MSIZE_1); // Memory data size

    // Double-buffer-mode is disabled by default

    // Configure addresses
    DMA2_Stream0->PAR = (uint32_t)&(ADC1->DR);
    DMA2_Stream0->M0AR = (uint32_t)results;

    // Enable stream
    DMA2_Stream0->NDTR = 16; // Number of items to transfer
    SET_BIT(DMA2_Stream0->CR, DMA_SxCR_EN); // Enable the DMA stream

    // *** ADC Configuration ***
    // Enable the DMA in the ADC's configuration
    SET_BIT(ADC1->CR2, ADC_CR2_DMA);
    SET_BIT(ADC1->CR2, ADC_CR2_DDS);

    // Configure all 16 channels to be sampled
    SET_BIT(ADC1->SQR1, ADC_SQR1_L_0 | ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3);

    // Enable ADC Scan mode
    SET_BIT(ADC1->CR1, ADC_CR1_SCAN);

    // Set the ADC Prescaler to [PCLK2 divided by 8]
    SET_BIT(ADC1_COMMON->CCR, ADC_CCR_ADCPRE_0);
    SET_BIT(ADC1_COMMON->CCR, ADC_CCR_ADCPRE_1);

    // Enable Continuous conversion mode
    SET_BIT(ADC1->CR2, ADC_CR2_CONT);

    // Enable the ADC with the ADON bit
    SET_BIT(ADC1->CR2, ADC_CR2_ADON);

    isInitialized = true;
}

void gpio::AnalogInput::init_specific_() {
    init_adc_();
    adc_addChannel(pin);
}

double gpio::AnalogInput::read_specific_() {
    // Ensure the ADC is running
    SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);

    // Wait for the current conversion to end
    while(!READ_BIT(ADC1->SR, ADC_SR_EOC)) { yield; }

    return (double)(*(pin.resultVariable) + 1) / 4096.0;
}

#endif /* LIBEMBED_PLATFORM == ststm32 */