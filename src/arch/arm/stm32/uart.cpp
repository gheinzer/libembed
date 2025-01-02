#include <libembed/arch/arm/stm32/uart.h>
#include <libembed/arch/arm/stm32/stm32_hal.h>
#include <libembed/exceptions.h>
#include "uart_types.h"

#if LIBEMBED_PLATFORM == ststm32

using namespace embed::arch::arm::stm32;

void uart::HardwareUART::begin(Baudrate baudrate, uint8_t wordLength, ParityMode parityMode, StopBitMode stopBitMode){
    __uart_clock_enable();

    uartHandle.Instance = interface.hwInterfacePtr;
    uartHandle.Init.BaudRate = baudrate;
    
    switch(wordLength) {
        case 8: uartHandle.Init.WordLength = UART_WORDLENGTH_8B; break;
        case 9: uartHandle.Init.WordLength = UART_WORDLENGTH_9B; break;
        default: throw embed::unsupported_on_this_device("Unsupported word length.");
    }

    switch(parityMode) {
        case PARITY_DISABLED: uartHandle.Init.Parity = UART_PARITY_NONE; break;
        case PARITY_EVEN: uartHandle.Init.Parity = UART_PARITY_EVEN; break;
        case PARITY_ODD: uartHandle.Init.Parity = UART_PARITY_ODD; break;
        default: embed::unsupported_on_this_device("Unsupported parity mode.");
    }

    switch(stopBitMode) {
        case STOPBIT_1: uartHandle.Init.StopBits = UART_STOPBITS_1; break;
        case STOPBIT_2: uartHandle.Init.StopBits = UART_STOPBITS_2; break;
        default: embed::unsupported_on_this_device("Unsupported stop bit mode.");
    }

    uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartHandle.Init.Mode = UART_MODE_TX_RX;
    uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
    HAL_UART_Init(&uartHandle);
}

void uart::HardwareUART::writeFrame(DataFrame data, uint32_t timeout) {
    if(uartHandle.Init.WordLength == UART_WORDLENGTH_8B) {
        uint8_t byte_data = data;
        HAL_UART_Transmit(&uartHandle, &byte_data, 1, timeout);
    } else {
        HAL_UART_Transmit(&uartHandle, (uint8_t*)&data, 1, timeout);
    }
}

uart::DataFrame uart::HardwareUART::recvFrame(uint32_t timeout) {
    DataFrame recvData;
    if(uartHandle.Init.WordLength == UART_WORDLENGTH_8B) {
        uint8_t recvData_byte;
        HAL_UART_Receive(&uartHandle, &recvData_byte, 1, timeout);
        recvData = recvData_byte;
    } else {
        HAL_UART_Receive(&uartHandle, (uint8_t*)&recvData, 1, timeout);
    }
    return recvData;
}

#endif /* LIBEMBED_PLATFORM == ststm32 */