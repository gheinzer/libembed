/**
 * @file nucleo_f412zg.h
 * @author Gabriel Heinzer
 * @brief BSP for ST Microelectronics NUCLEO-F412ZG
 */
#include <libembed/hal/gpio.h>
#include <libembed/hal/uart.h>

#ifndef LIBEMBED_BSP_DISCO_F412ZG_H_
#define LIBEMBED_BSP_DISCO_F412ZG_H_

namespace embed::board {
    //! BSP for ST Microelectronics NUCLEO-F412ZG
    namespace nucleo_f412zg {
        // *** Built-in LEDs ***
        //! LD1 (green LED)
        extern gpio::DigitalOutput LD1;
        //! Alias for @ref LD1
        extern gpio::DigitalOutput& led_green;

        //! LD2 (blue LED)
        extern gpio::DigitalOutput LD2;
        //! Alias for @ref LD2
        extern gpio::DigitalOutput& led_blue;

        //! LD3 (red LED)
        extern gpio::DigitalOutput LD3;
        //! Alias for @ref LD3
        extern gpio::DigitalOutput& led_red;


        // *** Built-in joystick ***
        //! Usr_but signal (user button B1)
        extern gpio::DigitalInput B1;
        //! Alias for @ref B1
        extern gpio::DigitalInput& user_button;

        //! UART interface for the virtual COM port VCP
        extern uart::HardwareUART UART_VCP;

        //! TX pin for the virtual COM port VCP
        extern embed::gpio::__GPIO_Pin& UART_VCP_TX;
        //! RX pin for the virtual COM port VCP
        extern embed::gpio::__GPIO_Pin& UART_VCP_RX;

        /**
         * @brief Initialize the VCP with the specified baudrate
         * 
         * @param baudrate The baudrate to use for the VCP.
         */
        void beginVCP(uart::Baudrate baudrate);
    }
}

#endif /* LIBEMBED_BSP_DISCO_F412ZG_H_ */