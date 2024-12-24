#include <libembed/hal/platforms/stm32/gpio.h>
#include <libembed/hal/gpio.h>

#if PIOPLATFORM == ststm32

using namespace embed;

__GPIO_DEFINEPORTS_C;

void gpio::init() {
    __FORALLPORTS_PS(__HAL_RCC_GPIO, _CLK_ENABLE());
}

// *** gpio::DigitalOutput ***
gpio::DigitalOutput::DigitalOutput(gpio::GPIO_Pin &gpio, GPIO_Flags flags) : gpio_(gpio) {
    gpio::init();

    GPIO_InitTypeDef initStruct;

    if(flags & GPIO_Flags::PULLUP) {
        initStruct.Pull = GPIO_PULLUP;
    } else if(flags & GPIO_Flags::PULLDOWN) {
        initStruct.Pull = GPIO_PULLDOWN;
    } else {
        initStruct.Pull = GPIO_NOPULL;
    }

    if(flags & GPIO_Flags::OPENDRAIN) {
        initStruct.Mode = GPIO_MODE_OUTPUT_OD;
    } else {
        initStruct.Mode = GPIO_MODE_OUTPUT_PP;
    }

    initStruct.Pin = gpio_.pin;
    initStruct.Speed = GPIO_SPEED_FAST;
    
    HAL_GPIO_Init(gpio_.port, &initStruct);
}

void gpio::DigitalOutput::write(bool state) {
    HAL_GPIO_WritePin(gpio_.port, gpio_.pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void gpio::DigitalOutput::toggle() {
    HAL_GPIO_TogglePin(gpio_.port, gpio_.pin);
}

// *** gpio::DigitalInput ***
gpio::DigitalInput::DigitalInput(GPIO_Pin &gpio, GPIO_Flags flags) : gpio_(gpio) {
    GPIO_InitTypeDef initStruct;

    if(flags & GPIO_Flags::PULLUP) {
        initStruct.Pull = GPIO_PULLUP;
    } else if(flags & GPIO_Flags::PULLDOWN) {
        initStruct.Pull = GPIO_PULLDOWN;
    } else {
        initStruct.Pull = GPIO_NOPULL;
    }

    initStruct.Pin = gpio_.pin;
    initStruct.Speed = GPIO_SPEED_FAST;
    initStruct.Mode = GPIO_MODE_INPUT;
    
    HAL_GPIO_Init(gpio_.port, &initStruct);
}

bool gpio::DigitalInput::read() { return HAL_GPIO_ReadPin(gpio_.port, gpio_.pin) == GPIO_PIN_SET; }

#endif /* PIOPLATFORM == ststm32 */