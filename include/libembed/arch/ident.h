/**
 * @file ident.h
 * @author Gabriel Heinzer
 * @brief Helper header for identifying devices.
 */

#include <libembed/util/macros.h>

#ifndef LIBEMBED_ARCH_IDENT_H_
#define LIBEMBED_ARCH_IDENT_H_

#define __ERROR_UNSUPPORTED_DEVICE static_assert(0 == 1, "This device is not supported. Please refer to the documentation for a complete list of supported devices.")

// *** Default values ***
// STM32
    //! Indicates that a STM32F412xx series MCU has been used
    #define STM32F412xx 0

// *** ARM-Specifics ***
#if __ARM_ARCH || __DOYXGEN__

    #undef LIBEMBED_MCU_ARCH
    #define LIBEMBED_MCU_ARCH arm

    // *** STM32-Specifics ***
    #if LIBEMBED_PLATFORM == ststm32

        #undef LIBEMBED_MCU_FAMILY
        #define LIBEMBED_MCU_FAMILY stm32

        #if STM32F4 || __DOYXGEN__

            #if STM32F412Zx || STM32F412Vx || STM32F412Rx || STM32F412Cx || __DOYXGEN__
                #define LIBEMBED_MCU_LINE stm32f412

                #undef STM32F412xx
                #define STM32F412xx 1
            #else
                __ERROR_UNSUPPORTED_DEVICE
            #endif

        #elif STM32G0
            #if STM32G031xx
                // For STM32G031, STM32G031xx is already defined
                #define LIBEMBED_MCU_LINE stm32g031
            #else
                __ERROR_UNSUPPORTED_DEVICE
            #endif
        #endif

    #endif /* STM32 */

#elif __DOXYGEN__

    //! Architecture of the microcontroller (e.g. `arm`)
    #define LIBEMBED_MCU_ARCH arm
    //! Family of the microcontroller (e.g. `stm32`)
    #define LIBEMBED_MCU_FAMILY stm32
    //! Line of the microcontroller (e.g. `stm32f412`)
    #define LIBEMBED_MCU_LINE stm32f412

    //! Indicates that a STM32F412xx series MCU has been used
    #define STM32F412xx 0

#else
    __ERROR_UNSUPPORTED_DEVICE
#endif

#endif /* LIBEMBED_ARCH_IDENT_H_ */