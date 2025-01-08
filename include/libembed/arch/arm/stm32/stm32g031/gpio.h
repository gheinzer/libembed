/**
 * @file gpio.h
 * @author Gabriel Heinzer
 * @brief STM32G0xx-specific GPIO definitions.
 */

#define __FORALLPORTS_PS(prefix, suffix) \
    LIBEMBED_CONCAT3(prefix, A, suffix); \
    LIBEMBED_CONCAT3(prefix, B, suffix); \
    LIBEMBED_CONCAT3(prefix, C, suffix); \
    LIBEMBED_CONCAT3(prefix, D, suffix)

#define __FORALLPORTS_F(function) \
    function(A); \
    function(B); \
    function(C); \
    function(D)

namespace embed::arch::arm::stm32::stm32f412::gpio {
    
}