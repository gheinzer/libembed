#include <libembed/hal/uart/types.h>
#include <libembed/arch/arch.h>
#include <libembed/arch/arm/stm32/stm32_hal.h>
#include <libembed/arch/ident.h>
#include <libembed/arch/arm/stm32/stm32f412/uart.h>
#include "../uart_types.h"

#if STM32F412xx

namespace embed::arch::arm::stm32::stm32f412::uart {
    UART_HardwareInterface UART1 = { 
        .hwInterfacePtr = USART1
    };
    UART_HardwareInterface UART2 = {
        .hwInterfacePtr = USART2
    };
    UART_HardwareInterface UART3 = {
        .hwInterfacePtr = USART3
    };
}

void embed::arch::arm::stm32::uart::__uart_clock_enable() {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();
}

#endif