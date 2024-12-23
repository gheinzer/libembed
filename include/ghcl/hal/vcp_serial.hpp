#include <ghcl/hal/stm32_hal.h>
#include <stdio.h>

#ifndef GHCL_HAL_VCP_SERIAL_HPP_
#define GHCL_HAL_VCP_SERIAL_HPP_

namespace ghcl::vcp_serial {
    extern UART_HandleTypeDef uartHandle;

    void init(unsigned long baudrate);
    
    void print(const char* msg);
}

#endif /* GHCL_HAL_VCP_SERIAL_HPP_ */