#include <libembed/hal/uart.h>

using namespace embed;

uart::UART_Base::UART_Base() { }
uart::HardwareUART_Base::HardwareUART_Base(uart::UART_HardwareInterface& interface) : UART_Base(), interface(interface) { }