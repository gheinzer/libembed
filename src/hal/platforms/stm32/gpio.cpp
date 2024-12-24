#include <libembed/hal/platforms/stm32/gpio.h>
#include <libembed/hal/gpio.h>

using namespace embed;

__GPIO_DEFINEPORTS_C;

void gpio::init() {
    __FORALLPORTS_PS(__HAL_RCC_GPIO, _CLK_ENABLE());
}

// *** gpio::DigitalOutput ***
gpio::DigitalOutput::DigitalOutput(gpio::GPIO_t &gpio, uint32_t mode) : gpio_(gpio) {
    GPIO_InitTypeDef initStruct;
    initStruct.Pull = GPIO_NOPULL;
    initStruct.Pin = gpio_.pin;
    initStruct.Speed = GPIO_SPEED_FAST;
    initStruct.Mode = mode;
    
    HAL_GPIO_Init(gpio_.port, &initStruct);
}

void gpio::DigitalOutput::enable() { write(true); }
void gpio::DigitalOutput::disable() { write(false); }

void gpio::DigitalOutput::write(bool state) {
    HAL_GPIO_WritePin(gpio_.port, gpio_.pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void gpio::DigitalOutput::toggle() {
    HAL_GPIO_TogglePin(gpio_.port, gpio_.pin);
}

// *** gpio::DigitalInput ***
gpio::DigitalInput::DigitalInput(GPIO_t &gpio, uint32_t mode) : gpio_(gpio) {
    GPIO_InitTypeDef initStruct;
    initStruct.Pull = GPIO_NOPULL;
    initStruct.Pin = gpio_.pin;
    initStruct.Speed = GPIO_SPEED_FAST;
    initStruct.Mode = mode;
    
    HAL_GPIO_Init(gpio_.port, &initStruct);
}

bool gpio::DigitalInput::read() { return HAL_GPIO_ReadPin(gpio_.port, gpio_.pin) == GPIO_PIN_SET; }