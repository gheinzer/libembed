#include <libembed/arch/arm/stm32/gpio.h>
#include <libembed/hal/gpio/types.h>
#include <libembed/arch/ident.h>

#if STM32

using namespace embed::arch::arm::stm32;

__GPIO_DEFINEPORTS_C;

void __enable_clocks() {
    __FORALLPORTS_PS(__HAL_RCC_GPIO, _CLK_ENABLE());
}

// *** gpio::__GPIO_Pin ***
void embed::gpio::_GPIO_Pin_specific::setAlternate(uint32_t alternate) {
    __enable_clocks();

    GPIO_InitTypeDef initStruct;
    initStruct.Pin = pin;
    initStruct.Alternate = alternate;
    initStruct.Mode = GPIO_MODE_AF_PP;
    initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    initStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(port, &initStruct);
}

void embed::gpio::_GPIO_Pin_specific::setAnalog() {
    __enable_clocks();

    GPIO_InitTypeDef initStruct;
    initStruct.Pin = pin;
    initStruct.Mode = GPIO_MODE_ANALOG;
    initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    initStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(port, &initStruct);
}

// *** gpio::DigitalOutput ***
void gpio::DigitalOutput::init_specific_() {
    __enable_clocks();
    GPIO_InitTypeDef initStruct;

    if(flags & embed::arch::arm::stm32::gpio::PULLUP) {
        initStruct.Pull = GPIO_PULLUP;
    } else if(flags & embed::arch::arm::stm32::gpio::PULLDOWN) {
        initStruct.Pull = GPIO_PULLDOWN;
    } else {
        initStruct.Pull = GPIO_NOPULL;
    }

    if(flags & embed::arch::arm::stm32::gpio::OPENDRAIN) {
        initStruct.Mode = GPIO_MODE_OUTPUT_OD;
    } else {
        initStruct.Mode = GPIO_MODE_OUTPUT_PP;
    }

    initStruct.Pin = gpio.pin;
    initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    
    HAL_GPIO_Init(gpio.port, &initStruct);
}

void gpio::DigitalOutput::write_specific_(bool state) {
    HAL_GPIO_WritePin(gpio.port, gpio.pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void gpio::DigitalOutput::toggle_specific_() {
    HAL_GPIO_TogglePin(gpio.port, gpio.pin);
}

bool gpio::DigitalOutput::read_specific_() {
    return HAL_GPIO_ReadPin(gpio.port, gpio.pin);
}

// *** gpio::DigitalInput ***
void gpio::DigitalInput::init_specific_() {
    __enable_clocks();
    GPIO_InitTypeDef initStruct;

    if(flags & embed::arch::arm::stm32::gpio::PULLUP) {
        initStruct.Pull = GPIO_PULLUP;
    } else if(flags & embed::arch::arm::stm32::gpio::PULLDOWN) {
        initStruct.Pull = GPIO_PULLDOWN;
    } else {
        initStruct.Pull = GPIO_NOPULL;
    }

    initStruct.Pin = gpio.pin;
    initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    initStruct.Mode = GPIO_MODE_INPUT;
    
    HAL_GPIO_Init(gpio.port, &initStruct);
}

bool gpio::DigitalInput::read_specific_() { 
    GPIO_PinState state = HAL_GPIO_ReadPin(gpio.port, gpio.pin);
    return state == GPIO_PIN_SET;
}

#endif /* LIBEMBED_PLATFORM == ststm32 */