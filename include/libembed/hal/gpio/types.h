/**
 * @file types.h
 * @author Gabriel Heinzer
 * @brief Common type definitions for @ref libembed/hal/gpio.h.
 */
#include <stdint.h>

#ifndef LIBEMBED_HAL_GPIO_TYPES_H_
#define LIBEMBED_HAL_GPIO_TYPES_H_

/**
 * @brief Classes for easily interfacing with general-purpose inputs and outputs.
 * 
 */
namespace embed::gpio {
    /**
     * @brief Opaque data structure defining a hardware pin.
     */
    typedef struct __GPIO_Pin GPIO_Pin;

    //! Platform-specific GPIO flags
    typedef const uint32_t GPIO_Flag;

    //! Placeholder value for no flags
    GPIO_Flag NO_FLAGS = 0;

    /**
     * @brief Represents a digital output pin.
     */
    class DigitalOutput {
        private:
            /**
             * @brief Platform-specific output set function.
             * 
             * This does not need to take inversion of the output into account.
             * 
             * @param state The state the output should be set to, without any inversion.
             */
            void write_specific_(bool state);

            /**
             * @brief Platform-specific output toggle function.
             * 
             */
            void toggle_specific_();

            /**
             * @brief Platform-specific output read function.
             * 
             * @return The state of the output, without any inversion.
             */
            bool read_specific_();

            /**
             * @brief Platform-specific initialization function.
             * 
             * Called automatically when constructing a DigitalOutput class instance.
             * 
             */
            void init_specific_();

        public:
            /**
             * @brief Initial state of the output.
             * 
             */
            const bool initialState;
            /**
             * @brief Whether the output is inverted or not.
             * 
             */
            const bool inverted;
            /**
             * @brief Platform-specific flags passed to the constructor.
             * 
             */
            const GPIO_Flag flags;
            /**
             * @brief GPIO pin assigned to the output.
             * 
             */
            const GPIO_Pin& gpio;

            /**
             * @brief Construct a new digital output object.
             * 
             * @param pin The GPIO pin you want to assign to the output.
             * @param inverted Whether the output shall be inverted or not.
             * @param initialState The initial state to write to the output.
             * @param flags Platform-specific flags for the output.
             */
            DigitalOutput(GPIO_Pin& pin, bool inverted = false, bool initialState = false, GPIO_Flag flags = NO_FLAGS);

            /**
             * @brief Construct a new digital output object.
             * 
             * @param pin The GPIO pin you want to assign to the output.
             * @param inverted Whether the output shall be inverted or not.
             * @param flags Platform-specific flags for the output.
             */
            DigitalOutput(GPIO_Pin& pin, bool inverted, GPIO_Flag flags);

            /**
             * @brief Construct a new digital output object.
             * 
             * @param pin The GPIO pin you want to assign to the output.
             * @param flags Platform-specific flags for the output.
             */
            DigitalOutput(GPIO_Pin& pin, GPIO_Flag flags);

            /**
             * @brief Sets the output to the specified state.
             * 
             * @param state The state you want to set the digital output to as a boolean.
             */
            void write(bool state);
            /**
             * @brief Toggles the output (inverts its value).
             * 
             */
            void toggle();
            /**
             * @brief Enables the output.
             * 
             */
            void enable();
            /**
             * @brief Disables the output.
             * 
             */
            void disable();
            /**
             * @brief Reads the state from the input.
             * 
             * @return The current state of the output.
             */
            bool read();

            /**
             * @brief Operator overload for the `=` operator. Sets the state of the output.
             * 
             * @param state Boolean state to set the output to.
             */
            inline void operator =(bool state) { write(state); }
            /**
             * @brief Operator overload for the `^=` operator. Performs an XOR operation with
             * the current state of the output.
             * 
             * @param op The input for the XOR operation.
             */
            inline void operator ^=(bool op) { if(op) toggle(); }

            /**
             * @brief Conversion overload for `bool`. Gets the current state of the output.
             * 
             * @return Returns the current state of the output.
             */
            inline operator bool() { return read(); }
    };

    /**
     * @brief Represents a digital input.
     */
    class DigitalInput {
        private:
            /**
             * @brief Platform-specific initialization function.
             * 
             * Called automatically when constructing a DigitalInput class instance.
             * 
             */
            void init_specific_();

            /**
             * @brief Platform-specific input read function.
             * 
             * This function does not need to take inversion into account.
             * 
             * @return Returns the digital state of the input, without any inversion.
             */
            bool read_specific_();

        public:
            /**
             * @brief Whether the input is inverted.
             * 
             */
            const bool inverted;
            /**
             * @brief Flags applied to the input.
             * 
             */
            const GPIO_Flag flags;
            /**
             * @brief The GPIO pin assigned to the input.
             * 
             */
            const GPIO_Pin& gpio;

            /**
             * @brief Construct a new digital niput object.
             * 
             * @param pin The GPIO pin you want to assign to the input.
             * @param inverted Whether the input shall be inverted or not.
             * @param flags Platform-specific flags for the input.
             */
            DigitalInput(GPIO_Pin& pin, bool inverted = false, GPIO_Flag flags = NO_FLAGS);

            /**
             * @brief Construct a new digital niput object.
             * 
             * @param pin The GPIO pin you want to assign to the input.
             * @param flags Platform-specific flags for the input.
             */
            DigitalInput(GPIO_Pin& pin, GPIO_Flag flags);

            /**
             * @brief Reads the value from the input and returns it as a boolean.
             * 
             * @return Returns the digital value of the input as a boolean.
             */
            bool read();

            /**
             * @brief Conversion overload for `bool`. Gets the current state of the input.
             * 
             * @return Returns the current state of the input.
             */
            inline operator bool() { return read(); }
    };
}

#endif /* LIBEMBED_HAL_GPIO_TYPES_H_ */