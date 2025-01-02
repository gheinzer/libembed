/**
 * @file gpio.h
 * @author Gabriel Heinzer
 * @brief GPIO definitions specific to STM32.
 */

#include "stm32_hal.h"
#include <libembed/hal/gpio/types.h>
#include <libembed/arch/ident.h>

#ifndef LIBEMBED_STM32_GPIO_H_
#define LIBEMBED_STM32_GPIO_H_

#include LIBEMBED_STRINGIFY(LIBEMBED_MCU_LINE/gpio.h)

#define __GPIO_DEFINEPIN_H(port, pin) extern GPIO_Pin P##port##pin;
#define __GPIO_DEFINEPIN_C(_port, _pin) embed::arch::arm::stm32::gpio::GPIO_Pin embed::arch::arm::stm32::gpio::P##_port##_pin = { .port = GPIO##_port, .pin = GPIO_PIN_##_pin , .pinNumber = _pin };

#define __GPIO_DEFINEPORT_H(port) __FORALLPINS_FPORT(__GPIO_DEFINEPIN_H, port)
#define __GPIO_DEFINEPORT_C(port) __FORALLPINS_FPORT(__GPIO_DEFINEPIN_C, port)

#define __GPIO_DEFINEPORTS_H __FORALLPORTS_F(__GPIO_DEFINEPORT_H)
#define __GPIO_DEFINEPORTS_C __FORALLPORTS_F(__GPIO_DEFINEPORT_C)

#define __FORALLPINS_FPORT(function, port) \
    function(port, 0); \
    function(port, 1); \
    function(port, 2); \
    function(port, 3); \
    function(port, 4); \
    function(port, 5); \
    function(port, 6); \
    function(port, 7); \
    function(port, 8); \
    function(port, 9); \
    function(port, 10); \
    function(port, 11); \
    function(port, 12); \
    function(port, 13); \
    function(port, 14); \
    function(port, 15);

#if STM32G031xx
    #include "stm32g031/gpio.h"
#elif STM32F412xx
    #include "stm32f412/gpio.h"
#endif

class embed::gpio::__GPIO_Pin {
    public:
        GPIO_TypeDef* port;
        uint32_t pin;
        uint32_t pinNumber;

        /**
         * @brief Set the GPIO pin to use the given alternate function.
         * 
         * @param alternate The alternate function to use.
         */
        void setAlternate(uint32_t alternate);
};

//! STM32-specific GPIO declarations
namespace embed::arch::arm::stm32::gpio {
    using namespace embed::gpio;

    //! Push-pull output configuration. Only applicable for outputs.
    GPIO_Flag PUSHPULL = 1;

    //! Open-drain output configuration. Only applicable for outputs.
    GPIO_Flag OPENDRAIN = 2;

    //! Pull-up input configuration. Only applicable for inputs.
    GPIO_Flag PULLUP = 4;

    //! Pull-down input configuration. Only applicable for inputs.
    GPIO_Flag PULLDOWN = 8;

    __GPIO_DEFINEPORTS_H;
}

#endif /* LIBEMBED_STM32_GPIO_H_ */