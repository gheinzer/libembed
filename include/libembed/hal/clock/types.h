/**
 * @file types.h
 * @author Gabriel Heinzer
 * @brief Common type definitions for @ref libembed/hal/clock.h.
 */

#ifndef LIBEMBED_HAL_CLOCK_TYPES_H_
#define LIBEMBED_HAL_CLOCK_TYPES_H_

/**
 * @brief Hardware abstraction layer for clock control.
 * 
 */
namespace embed::clock {
    /**
     * @brief Initializes the clock control HAL.
     * 
     */
    void init();

    /**
     * @brief Delay the execution for the specified number of milliseconds.
     * 
     * This function is coroutine-compatible, i.e. yields periodically.
     * 
     * @param milliseconds The number of milliseconds you want to pause the execution for.
     */
    void delay(unsigned int milliseconds);

    /**
     * @brief Configures the microcontroller to run on the highest available
     * internal oscillator with the highest possible frequency.
     * 
     * This may not be available on all platforms.
     */
    void setMaximumFrequency();
};

#endif /* LIBEMBED_HAL_CLOCK_TYPES_H_ */