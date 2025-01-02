#include <libembed/hal/uart/types.h>
#include <libembed/arch/arch.h>
#include <libembed/arch/arm/stm32/stm32_hal.h>
#include <libembed/arch/ident.h>
#include <libembed/arch/arm/stm32/stm32g031/uart.h>
#include "../uart_types.h"

#if STM32G031xx

namespace embed::arch::arm::stm32::stm32g031::uart {
    UART_HardwareInterface UART1 = { 
        .hwInterfacePtr = USART1
    };
    UART_HardwareInterface UART2 = {
        .hwInterfacePtr = USART2
    };
}

void embed::arch::arm::stm32::uart::__uart_clock_enable() {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
}

#endif