/**
 * @file uart.h
 * @author Gabriel Heinzer
 * @brief UART HAL specific to STM32.
 */

#include <libembed/hal/uart/types.h>
#include <libembed/arch/ident.h>
#include "stm32_hal.h"

#ifndef LIBEMBED_ARCH_ARM_STM32_UART_H_
#define LIBEMBED_ARCH_ARM_STM32_UART_H_

#include LIBEMBED_STRINGIFY(LIBEMBED_MCU_LINE/uart.h)

//! STM32-specific UART implementation
namespace embed::arch::arm::stm32::uart {
    using namespace embed::uart;
    using namespace embed::arch::arm::stm32::LIBEMBED_MCU_LINE::uart;

    /**
     * @brief STM32 implementation of a hardware UART interface.
     */
    class HardwareUART : public HardwareUART_Base {
        private:
            //! UART Handle for the STM32 HALs
            UART_HandleTypeDef uartHandle;

        public:
            using HardwareUART_Base::HardwareUART_Base;

            void begin(Baudrate baudrate = 9600, uint8_t wordLength = 8, ParityMode parityMode = PARITY_DISABLED, StopBitMode stopBitMode = STOPBIT_1) override;

            void writeFrame(DataFrame data, uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT) override;
            DataFrame recvFrame(uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_RECV_TIMEOUT) override;
    };
}

#endif /* LIBEMBED_ARCH_ARM_STM32_UART_H_ */