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

    //! Analog input pin PA0 (handled by ADC1, channel 0)
    extern AnalogInput_Pin PA0_ADC1_0;
    //! Analog input pin PA1 (handled by ADC1, channel 1)
    extern AnalogInput_Pin PA1_ADC1_1;
    //! Analog input pin PA2 (handled by ADC1, channel 2)
    extern AnalogInput_Pin PA2_ADC1_2;
    //! Analog input pin PA3 (handled by ADC1, channel 3)
    extern AnalogInput_Pin PA3_ADC1_3;
    //! Analog input pin PA4 (handled by ADC1, channel 4)
    extern AnalogInput_Pin PA4_ADC1_4;
    //! Analog input pin PA5 (handled by ADC1, channel 5)
    extern AnalogInput_Pin PA5_ADC1_5;
    //! Analog input pin PA6 (handled by ADC1, channel 6)
    extern AnalogInput_Pin PA6_ADC1_6;
    //! Analog input pin PA7 (handled by ADC1, channel 7)
    extern AnalogInput_Pin PA7_ADC1_7;
    //! Analog input pin PB0 (handled by ADC1, channel 8)
    extern AnalogInput_Pin PB0_ADC1_8;
    //! Analog input pin PB1 (handled by ADC1, channel 9)
    extern AnalogInput_Pin PB1_ADC1_9;
    //! Analog input pin PC0 (handled by ADC1, channel 10)
    extern AnalogInput_Pin PC0_ADC1_10;
    //! Analog input pin PC1 (handled by ADC1, channel 11)
    extern AnalogInput_Pin PC1_ADC1_11;
    //! Analog input pin PC2 (handled by ADC1, channel 12)
    extern AnalogInput_Pin PC2_ADC1_12;
    //! Analog input pin PC3 (handled by ADC1, channel 13)
    extern AnalogInput_Pin PC3_ADC1_13;
    //! Analog input pin PC4 (handled by ADC1, channel 14)
    extern AnalogInput_Pin PC4_ADC1_14;
    //! Analog input pin PC5 (handled by ADC1, channel 15)
    extern AnalogInput_Pin PC5_ADC1_15;
}