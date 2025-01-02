/**
 * @file arm.h
 * @author Gabriel Heinzer
 * @brief Root header file for ARM-specific implementations.
 */

#include <libembed/arch/ident.h>
#include LIBEMBED_STRINGIFY(LIBEMBED_MCU_FAMILY/LIBEMBED_MCU_FAMILY.h)

/**
 * @brief ARM-specific declarations.
 */
namespace embed::arch::arm {
    using namespace LIBEMBED_MCU_FAMILY;
}