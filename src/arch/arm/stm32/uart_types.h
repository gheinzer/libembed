#include <libembed/arch/arm/stm32/stm32_hal.h>

namespace embed::arch::arm::stm32::uart {
    void __uart_clock_enable();
}

namespace embed::uart {
    struct __UART_HardwareInterface {
        USART_TypeDef* hwInterfacePtr;
        uint32_t gpioAlternateFunctionID;
    };
}