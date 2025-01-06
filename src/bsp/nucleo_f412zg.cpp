#include <libembed/bsp/autobsp.h>
#include <libembed/util/debug.h>
#include <libembed/config.h>
#include <string>

#if LIBEMBED_BOARD_NUCLEO_F412ZG

    using namespace embed;

    gpio::DigitalOutput board::LD1(gpio::PB0, false);
    gpio::DigitalOutput board::LD2(gpio::PB7, false);
    gpio::DigitalOutput board::LD3(gpio::PB14, false);

    gpio::DigitalInput board::B1(gpio::PC13, true, gpio::PULLDOWN);

    gpio::DigitalOutput& board::led_green = LD1;
    gpio::DigitalOutput& board::led_blue = LD2;
    gpio::DigitalOutput& board::led_red = LD3;
    gpio::DigitalInput& board::user_button = B1;

    uart::HardwareUART board::UART_VCP(uart::UART3);
    gpio::__GPIO_Pin& board::UART_VCP_TX = gpio::PD8;
    gpio::__GPIO_Pin& board::UART_VCP_RX = gpio::PD9;

    static void __vcp_write(std::string data) {
        board::UART_VCP.write(data);
    }

    void board::nucleo_f412zg::beginVCP(uart::Baudrate baudrate) {
        board::UART_VCP_RX.setAlternate(GPIO_AF7_USART3);
        board::UART_VCP_TX.setAlternate(GPIO_AF7_USART3);
        board::UART_VCP.begin(baudrate);

        #if LIBEMBED_CONFIG_ENABLE_DEBUGGING
            debug::writeStringPtr = __vcp_write;
        #endif

        libembed_debug_info("VCP initialized by BSP.")
    }

#endif