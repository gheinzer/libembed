/**
 * @file arm.h
 * @author Gabriel Heinzer
 * @brief Root header file for ARM-specific implementations.
 */

#if LIBEMBED_PLATFORM == ststm32
    #include "stm32/stm32.h"
#endif /* LIBEMBED_PLATFORM == ststm32 */

/**
 * @brief ARM-specific declarations.
 */
namespace embed::arch::arm {
    #if LIBEMBED_PLATFORM == ststm32
        using namespace stm32;
    #endif /* LIBEMBED_PLATFORM == ststm32 */
}