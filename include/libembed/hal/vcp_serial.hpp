#include <libembed/hal/stm32_hal.h>
#include <stdio.h>

#ifndef LIBEMBED_HAL_VCP_SERIAL_HPP_
#define LIBEMBED_HAL_VCP_SERIAL_HPP_

namespace embd::vcp_serial {
    extern UART_HandleTypeDef uartHandle;

    void init(unsigned long baudrate);
    
    void print(const char* msg);
}

#endif /* LIBEMBED_HAL_VCP_SERIAL_HPP_ */