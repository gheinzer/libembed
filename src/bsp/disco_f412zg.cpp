#include <libembed/bsp/autobsp.h>
#include <libembed/util/debug.h>
#include <libembed/config.h>
#include <string>

#if LIBEMBED_BOARD_DISCO_F412ZG

    using namespace embed;

    gpio::DigitalOutput board::LD1(gpio::PE0, true);
    gpio::DigitalOutput board::LD2(gpio::PE1, true);
    gpio::DigitalOutput board::LD3(gpio::PE2, true);
    gpio::DigitalOutput board::LD4(gpio::PE3, true);

    gpio::DigitalInput board::JOY_SEL(gpio::PA0, false, gpio::PULLDOWN);
    gpio::DigitalInput board::JOY_DOWN(gpio::PG1, false, gpio::PULLDOWN);
    gpio::DigitalInput board::JOY_LEFT(gpio::PF15, false, gpio::PULLDOWN);
    gpio::DigitalInput board::JOY_RIGHT(gpio::PF14, false, gpio::PULLDOWN);
    gpio::DigitalInput board::JOY_UP(gpio::PG0, false, gpio::PULLDOWN);

    gpio::DigitalOutput& board::led_green = LD1;
    gpio::DigitalOutput& board::led_orange = LD2;
    gpio::DigitalOutput& board::led_red = LD3;
    gpio::DigitalOutput& board::led_blue = LD4;
    gpio::DigitalInput& board::joystick_down = JOY_DOWN;
    gpio::DigitalInput& board::joystick_up = JOY_UP;
    gpio::DigitalInput& board::joystick_right = JOY_RIGHT;
    gpio::DigitalInput& board::joystick_left = JOY_LEFT;
    gpio::DigitalInput& board::joystick_selection = JOY_SEL;

    uart::HardwareUART board::UART_VCP(uart::UART2);
    gpio::_GPIO_Pin_specific& board::UART_VCP_TX = gpio::PA2;
    gpio::_GPIO_Pin_specific& board::UART_VCP_RX = gpio::PA3;

    gpio::_GPIO_Pin_specific& board::arduino::A0 = gpio::PA1;
    gpio::_GPIO_Pin_specific& board::arduino::A1 = gpio::PC1;
    gpio::_GPIO_Pin_specific& board::arduino::A2 = gpio::PC3;
    gpio::_GPIO_Pin_specific& board::arduino::A3 = gpio::PC4;
    gpio::_GPIO_Pin_specific& board::arduino::A4 = gpio::PC5;
    gpio::_GPIO_Pin_specific& board::arduino::A5 = gpio::PB0;
    gpio::_GPIO_Pin_specific& board::arduino::D0 = gpio::PG9;
    gpio::_GPIO_Pin_specific& board::arduino::D1 = gpio::PG14;
    gpio::_GPIO_Pin_specific& board::arduino::D2 = gpio::PG13;
    gpio::_GPIO_Pin_specific& board::arduino::D3 = gpio::PF4;
    gpio::_GPIO_Pin_specific& board::arduino::D4 = gpio::PG12;
    gpio::_GPIO_Pin_specific& board::arduino::D5 = gpio::PF10;
    gpio::_GPIO_Pin_specific& board::arduino::D6 = gpio::PF3;
    gpio::_GPIO_Pin_specific& board::arduino::D7 = gpio::PG11;
    gpio::_GPIO_Pin_specific& board::arduino::D8 = gpio::PG10;
    gpio::_GPIO_Pin_specific& board::arduino::D9 = gpio::PB8;
    gpio::_GPIO_Pin_specific& board::arduino::D10 = gpio::PA15;
    gpio::_GPIO_Pin_specific& board::arduino::D11 = gpio::PA7;
    gpio::_GPIO_Pin_specific& board::arduino::D12 = gpio::PA6;
    gpio::_GPIO_Pin_specific& board::arduino::D13 = gpio::PA5;
    gpio::_GPIO_Pin_specific& board::arduino::D14 = gpio::PB9;
    gpio::_GPIO_Pin_specific& board::arduino::D15 = gpio::PB10;

    static void __vcp_write(std::string data) {
        board::UART_VCP.write(data);
    }

    void board::beginVCP(uart::Baudrate baudrate) {
        board::UART_VCP_RX.setAlternate(GPIO_AF7_USART2);
        board::UART_VCP_TX.setAlternate(GPIO_AF7_USART2);
        board::UART_VCP.begin(baudrate);

        #if LIBEMBED_CONFIG_ENABLE_DEBUGGING
            debug::writeStringPtr = __vcp_write;
        #endif

        libembed_debug_info("VCP initialized by BSP.")
    }

#endif