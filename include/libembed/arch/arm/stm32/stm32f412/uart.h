#include <libembed/hal/uart/types.h>

namespace embed::arch::arm::stm32::stm32f412::uart {
    using namespace embed::uart;

    extern UART_HardwareInterface UART1;
    extern UART_HardwareInterface UART2;
    extern UART_HardwareInterface UART3;
};