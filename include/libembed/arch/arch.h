/**
 * @file arch.h
 * @author Gabriel Heinzer
 * @brief Conditional includes for including the right architecture- and platform-specific implementations.
 */

#ifdef __ARM_ARCH
    #include "arm/arm.h"
#endif /* __ARM_ARCH */

/**
 * @brief Architecture- and platform specific declarations.
 */
namespace embed::arch {
    #ifdef __ARM_ARCH
        using namespace arm;
    #endif /* __ARM_ARCH */
}