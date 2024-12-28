/**
 * @file gpio.h
 * @author Gabriel Heinzer
 * @brief STM32F4xx-specific GPIO definitions.
 */

#include <libembed/util/macros.h>

#define __FORALLPORTS_PS(prefix, suffix) \
    LIBEMBED_CONCAT3(prefix, A, suffix); \
    LIBEMBED_CONCAT3(prefix, B, suffix); \
    LIBEMBED_CONCAT3(prefix, C, suffix); \
    LIBEMBED_CONCAT3(prefix, D, suffix); \
    LIBEMBED_CONCAT3(prefix, E, suffix); \
    LIBEMBED_CONCAT3(prefix, F, suffix); \
    LIBEMBED_CONCAT3(prefix, G, suffix); \
    LIBEMBED_CONCAT3(prefix, H, suffix)

#define __FORALLPORTS_F(function) \
    function(A); \
    function(B); \
    function(C); \
    function(D); \
    function(E); \
    function(F); \
    function(G); \
    function(H)
