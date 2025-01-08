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

namespace embed::arch::arm::stm32::stm32f412::gpio {
    using namespace embed::gpio;

    extern AnalogInput_Pin ADC1_0;
    extern AnalogInput_Pin ADC1_1;
    extern AnalogInput_Pin ADC1_2;
    extern AnalogInput_Pin ADC1_3;
    extern AnalogInput_Pin ADC1_4;
    extern AnalogInput_Pin ADC1_5;
    extern AnalogInput_Pin ADC1_6;
    extern AnalogInput_Pin ADC1_7;
    extern AnalogInput_Pin ADC1_8;
    extern AnalogInput_Pin ADC1_9;
    extern AnalogInput_Pin ADC1_10;
    extern AnalogInput_Pin ADC1_11;
    extern AnalogInput_Pin ADC1_12;
    extern AnalogInput_Pin ADC1_13;
    extern AnalogInput_Pin ADC1_14;
    extern AnalogInput_Pin ADC1_15;
}