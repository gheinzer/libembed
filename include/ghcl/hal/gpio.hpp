#include <ghcl/hal/stm32_hal.h>
#include <ghcl/hal/_specifics.h>

#ifndef GHCL_HAL_GPIO_HPP_
#define GHCL_HAL_GPIO_HPP_

#define __GPIO_DEFINEPIN_H(port, pin) extern GPIO P##port##pin;
#define __GPIO_DEFINEPIN_C(_port, _pin) gpio::GPIO gpio::P##_port##_pin = { .port = GPIO##_port, .pin = GPIO_PIN_##_pin };

#define __GPIO_DEFINEPORT_H(port) __FORALLPINS_FPORT(__GPIO_DEFINEPIN_H, port)
#define __GPIO_DEFINEPORT_C(port) __FORALLPINS_FPORT(__GPIO_DEFINEPIN_C, port)

#define __GPIO_DEFINEPORTS_H __FORALLPORTS_F(__GPIO_DEFINEPORT_H)
#define __GPIO_DEFINEPORTS_C __FORALLPORTS_F(__GPIO_DEFINEPORT_C)

namespace gpio {
    typedef struct {
        GPIO_TypeDef* port;
        uint32_t pin;
    } GPIO;

    class DigitalOutput {
        private:
            GPIO &gpio_;

        public:
            DigitalOutput(GPIO &gpio, uint32_t mode, uint32_t speed = GPIO_SPEED_FREQ_HIGH);

            void write(bool state);
            void toggle();
            void enable();
            void disable();
    };

    class DigitalInput {
        private:
            GPIO &gpio_;

        public:
            DigitalInput(GPIO &gpio, uint32_t mode, uint32_t pull = GPIO_NOPULL, uint32_t speed = GPIO_SPEED_FREQ_HIGH);

            bool read();
    };

    __GPIO_DEFINEPORTS_H;
}

#endif /* GHCL_HAL_GPIO_HPP_ */