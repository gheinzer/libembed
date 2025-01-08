#include <libembed/arch/arm/stm32/stm32_hal.h>
#include <libembed/hal/gpio.h>

namespace embed::i2c {
    struct __I2C_HardwareInterface {
        I2C_TypeDef* interface;
    };
}