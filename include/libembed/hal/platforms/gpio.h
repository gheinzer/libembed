/**
 * @file gpio.h
 * @author Gabriel Heinzer
 * @brief Conditional includes for including the right GPIO definitions.
 */

#if LIBEMBED_PLATFORM == ststm32
    #include "stm32/gpio.h"
#endif /* STM32 */