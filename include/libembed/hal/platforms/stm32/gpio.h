#include "stm32_hal.h"
#include <libembed/hal/gpio/types.h>

#ifndef LIBEMBED_STM32_GPIO_H_
#define LIBEMBED_STM32_GPIO_H_

#define __GPIO_DEFINEPIN_H(port, pin) extern GPIO_Pin P##port##pin;
#define __GPIO_DEFINEPIN_C(_port, _pin) embed::gpio::GPIO_Pin embed::gpio::P##_port##_pin = { .port = GPIO##_port, .pin = GPIO_PIN_##_pin };

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

#ifdef STM32G0
    #include "stm32g0/gpio.h"
#endif

#ifdef STM32F4
    #include "stm32f4/gpio.h"
#endif

namespace embed::gpio {
    struct __GPIO_Pin {
        GPIO_TypeDef* port;
        uint32_t pin;
    };

    struct __GPIO_Flags {
        enum value {
            NONE = 0,
            PUSHPULL = 1,
            OPENDRAIN = 2,
            PULLUP = 4,
            PULLDOWN = 8
        };
    };

    class DigitalOutput : public __DigitalOutput_Base {
        private:
            GPIO_Pin& gpio_;

        public:
            DigitalOutput(GPIO_Pin& gpio, uint32_t flags = GPIO_Flags::NONE);

            void write(bool state) override;
            void toggle() override;
            void enable() override;
            void disable() override;
    };

    class DigitalInput : public __DigitalInput_Base {
        private:
            GPIO_Pin& gpio_;

        public:
            DigitalInput(GPIO_Pin& gpio, uint32_t flags = GPIO_Flags::NONE);

            bool read() override;
    };

    __GPIO_DEFINEPORTS_H;
}

#endif /* LIBEMBED_STM32_GPIO_H_ */