/**
 * @file disco_f412zg.h
 * @author Gabriel Heinzer
 * @brief BSP for ST Microelectronics 32F412GDISCOVERY
 */
#include <libembed/hal/gpio.h>
#include <libembed/hal/uart.h>

#ifndef LIBEMBED_BSP_DISCO_F412ZG_H_
#define LIBEMBED_BSP_DISCO_F412ZG_H_

namespace embed::board {
    //! BSP for ST Microelectronics 32F412GDISCOVERY
    namespace disco_f412zg {
        // *** Built-in LEDs ***
        //! LD1 (green LED)
        extern gpio::DigitalOutput LD1;
        //! Alias for @ref LD1
        extern gpio::DigitalOutput& led_green;

        //! LD2 (orange LED)
        extern gpio::DigitalOutput LD2;
        //! Alias for @ref LD2
        extern gpio::DigitalOutput& led_orange;

        //! LD3 (red LED)
        extern gpio::DigitalOutput LD3;
        //! Alias for @ref LD3
        extern gpio::DigitalOutput& led_red;
        
        //! LD4 (blue LED)
        extern gpio::DigitalOutput LD4;
        //! Alias for @ref LD4
        extern gpio::DigitalOutput& led_blue;


        // *** Built-in joystick ***
        //! Joystick down signal
        extern gpio::DigitalInput JOY_DOWN;
        //! Alias for @ref JOY_DOWN
        extern gpio::DigitalInput& joystick_down;

        //! Joystick up signal
        extern gpio::DigitalInput JOY_UP;
        //! Alias for @ref JOY_UP
        extern gpio::DigitalInput& joystick_up;

        //! Joystick right signal
        extern gpio::DigitalInput JOY_RIGHT;
        //! Alias for @ref JOY_RIGHT
        extern gpio::DigitalInput& joystick_right;

        //! Joystick left signal
        extern gpio::DigitalInput JOY_LEFT;
        //! Alias for @ref JOY_LEFT
        extern gpio::DigitalInput& joystick_left;

        //! Joystick select signal
        extern gpio::DigitalInput JOY_SEL;
        //! Alias for @ref JOY_SEL
        extern gpio::DigitalInput& joystick_selection;

        //! UART interface for the virtual COM port VCP
        extern uart::HardwareUART UART_VCP;

        //! TX pin for the virtual COM port VCP
        extern embed::gpio::_GPIO_Pin_specific& UART_VCP_TX;
        //! RX pin for the virtual COM port VCP
        extern embed::gpio::_GPIO_Pin_specific& UART_VCP_RX;

        /**
         * @brief Initialize the VCP with the specified baudrate
         * 
         * @param baudrate The baudrate to use for the VCP.
         */
        void beginVCP(uart::Baudrate baudrate);

        //! Arduino connector of the 32F412GDISCOVERY
        namespace arduino {
            //! Arduino connector analog pin A0
            extern gpio::_GPIO_Pin_specific& A0;
            //! Arduino connector analog pin A1
            extern gpio::_GPIO_Pin_specific& A1;
            //! Arduino connector analog pin A2
            extern gpio::_GPIO_Pin_specific& A2;
            //! Arduino connector analog pin A3
            extern gpio::_GPIO_Pin_specific& A3;
            //! Arduino connector analog pin A4
            extern gpio::_GPIO_Pin_specific& A4;
            //! Arduino connector analog pin A5
            extern gpio::_GPIO_Pin_specific& A5;

            //! Arduino connector digital pin D0
            extern gpio::_GPIO_Pin_specific& D0;
            //! Arduino connector digital pin D1
            extern gpio::_GPIO_Pin_specific& D1;
            //! Arduino connector digital pin D2
            extern gpio::_GPIO_Pin_specific& D2;
            //! Arduino connector digital pin D3
            extern gpio::_GPIO_Pin_specific& D3;
            //! Arduino connector digital pin D4
            extern gpio::_GPIO_Pin_specific& D4;
            //! Arduino connector digital pin D5
            extern gpio::_GPIO_Pin_specific& D5;
            //! Arduino connector digital pin D6
            extern gpio::_GPIO_Pin_specific& D6;
            //! Arduino connector digital pin D7
            extern gpio::_GPIO_Pin_specific& D7;
            //! Arduino connector digital pin D8
            extern gpio::_GPIO_Pin_specific& D8;
            //! Arduino connector digital pin D9
            extern gpio::_GPIO_Pin_specific& D9;
            //! Arduino connector digital pin D10
            extern gpio::_GPIO_Pin_specific& D10;
            //! Arduino connector digital pin D11
            extern gpio::_GPIO_Pin_specific& D11;
            //! Arduino connector digital pin D12
            extern gpio::_GPIO_Pin_specific& D12;
            //! Arduino connector digital pin D13
            extern gpio::_GPIO_Pin_specific& D13;
            //! Arduino connector digital pin D14
            extern gpio::_GPIO_Pin_specific& D14;
            //! Arduino connector digital pin D15
            extern gpio::_GPIO_Pin_specific& D15;
        }
    }
}

#endif /* LIBEMBED_BSP_DISCO_F412ZG_H_ */