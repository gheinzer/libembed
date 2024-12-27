/**
 * @file stm32_hal.h
 * @author Gabriel Heinzer
 * @brief Includes the proper HAL libraries for the STM32 processor.
 */

#ifdef STM32G0
    #include "stm32g0xx_hal.h"
#endif
#ifdef STM32F4
    #include "stm32f4xx_hal.h"
#endif