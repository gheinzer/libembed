#include <libembed/arch/arm/stm32/gpio.h>
#include <libembed/hal/gpio/types.h>

#if LIBEMBED_PLATFORM == ststm32

using namespace embed::arch::arm::stm32;

struct embed::gpio::__GPIO_Pin {
    GPIO_TypeDef* port;
    uint32_t pin;
    uint32_t pinNumber;
};

__GPIO_DEFINEPORTS_C;

void __enable_clocks() {
    __FORALLPORTS_PS(__HAL_RCC_GPIO, _CLK_ENABLE());
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
    initStruct.Speed = GPIO_SPEED_FAST;
    
    HAL_GPIO_Init(gpio.port, &initStruct);
}

void gpio::DigitalOutput::write_specific_(bool state) {
    HAL_GPIO_WritePin(gpio.port, gpio.pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void gpio::DigitalOutput::toggle_specific_() {
    HAL_GPIO_TogglePin(gpio.port, gpio.pin);
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
    initStruct.Speed = GPIO_SPEED_FAST;
    initStruct.Mode = GPIO_MODE_INPUT;
    
    HAL_GPIO_Init(gpio.port, &initStruct);
}

bool gpio::DigitalInput::read_specific_() { 
    GPIO_PinState state = HAL_GPIO_ReadPin(gpio.port, gpio.pinNumber);
    return state == GPIO_PIN_SET;
}

#endif /* LIBEMBED_PLATFORM == ststm32 */