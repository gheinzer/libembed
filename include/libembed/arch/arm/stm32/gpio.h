/**
 * @file gpio.h
 * @author Gabriel Heinzer
 * @brief GPIO definitions specific to STM32.
 */

#include "stm32_hal.h"
#include <libembed/hal/gpio/types.h>

#ifndef LIBEMBED_STM32_GPIO_H_
#define LIBEMBED_STM32_GPIO_H_

#define __GPIO_DEFINEPIN_H(port, pin) extern GPIO_Pin P##port##pin;
#define __GPIO_DEFINEPIN_C(_port, _pin) embed::arch::arm::stm32::gpio::GPIO_Pin embed::arch::arm::stm32::gpio::P##_port##_pin = { .port = GPIO##_port, .pin = GPIO_PIN_##_pin };

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

//! STM32-specific GPIO declarations
namespace embed::arch::arm::stm32::gpio {
    using namespace embed::gpio;

    /**
     * @brief STM32-specific list of flags for GPIO initializations.
     * 
     */
    typedef enum {
        /**
         * @brief Default value, no flags.
         * 
         */
        NO_FLAGS = 0,
        /**
         * @brief Push-pull output configuration. Only applicable for outputs.
         */
        PUSHPULL = 1,
        /**
         * @brief Open-drain output configuration. Only applicable for outputs.
         */
        OPENDRAIN = 2,
        /**
         * @brief Pull-up input configuration. Only applicable for inputs.
         */
        PULLUP = 4,
        /**
         * @brief Pull-down input configuration. Only applicable for inputs.
         */
        PULLDOWN = 8
    } GPIO_Flags;

    /**
     * @brief STM32-specific implementation of a digital output.
     * 
     */
    class DigitalOutput : public DigitalOutput_Base {
        private:
            GPIO_Pin& gpio_;

        public:
            /**
             * @brief Construct a new DigitalOutput object from the given GPIO pin.
             * 
             * @param gpio The GPIO pin the digital output references.
             * @param flags Flags for additional configuration.
             * 
             * @warning Use @p flags with caution as it is platform-specific.
             */
            DigitalOutput(GPIO_Pin& gpio, GPIO_Flags flags = NO_FLAGS);

            void write(bool state) override;
            void toggle() override;
    };

    /**
     * @brief STM32-specific implementation of a digital input.
     * 
     */
    class DigitalInput : public DigitalInput_Base {
        private:
            GPIO_Pin& gpio_;

        public:
            /**
             * @brief Construct a new DigitalInput object from the given GPIO pin.
             * 
             * @param gpio The GPIO pin the digital input references.
             * @param flags Flags for additional configuration.
             * 
             * @warning Use @p flags with caution as it is platform-specific.
             */
            DigitalInput(GPIO_Pin& gpio, GPIO_Flags flags = NO_FLAGS);

            bool read() override;
    };

    __GPIO_DEFINEPORTS_H;
}

#endif /* LIBEMBED_STM32_GPIO_H_ */