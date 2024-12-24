/**
 * @file types.h
 * @author Gabriel Heinzer
 * @brief Internal type definitions for 
 */
#include <stdint.h>

#ifndef LIBEMBED_HAL_GPIO_HPP_
#define LIBEMBED_HAL_GPIO_HPP_

namespace embed::gpio {
    void init();

    /**
     * @brief Opaque data structure defining a hardware pin.
     */
    typedef struct __GPIO_Pin GPIO_Pin;

    /**
     * @brief Base class for digital output pins.
     * Do not use this class directly. Use the 
     * platform-specific @ref DigitalOutput instead.
     */
    class DigitalOutput_Base {
        public:
            /**
             * @brief Sets the output to the specified state.
             * 
             * @param state The state you want to set the digital output to as a boolean.
             */
            virtual void write(bool state);
            /**
             * @brief Toggles the output (inverts its value).
             * 
             */
            virtual void toggle();
            /**
             * @brief Enables the output.
             * 
             */
            void enable() { write(true); };
            /**
             * @brief Disables the output.
             * 
             */
            virtual void disable() { write(false); }
    };

    /**
     * @brief Base class for digital input pins.
     * Do not use this class directly. Use the 
     * platform-specific @ref DigitalInput instead.
     */
    class DigitalInput_Base {
        public:
            /**
             * @brief Reads the value from the input and returns it as a boolean.
             * 
             * @return Returns the digital value of the input as a boolean.
             */
            virtual bool read();
    };
}

#endif /* LIBEMBED_HAL_GPIO_HPP_ */