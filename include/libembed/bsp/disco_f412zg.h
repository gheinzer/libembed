/**
 * @file disco_f412zg.H
 * @author Gabriel Heinzer
 * @brief BSP for ST Microelectronics 32F412GDISCOVERY
 */
#include <libembed/hal/gpio.h>

#ifndef LIBEMBED_BSP_DISCO_F412ZG_H_
#define LIBEMBED_BSP_DISCO_F412ZG_H_

namespace embed::board {
    //! BSP for ST Microelectronics 32F412GDISCOVERY
    inline namespace disco_f412zg {
        // *** Built-in LEDs ***
        //! LD1 (green LED)
        extern gpio::DigitalOutput LD1;
        //! Alias for @ref LD1
        gpio::DigitalOutput& led_green = LD1;

        //! LD2 (orange LED)
        extern gpio::DigitalOutput LD2;
        //! Alias for @ref LD1
        gpio::DigitalOutput& led_orange = LD2;

        //! LD3 (red LED)
        extern gpio::DigitalOutput LD3;
        //! Alias for @ref LD3
        gpio::DigitalOutput& led_red = LD3;
        
        //! LD4 (blue LED)
        extern gpio::DigitalOutput LD4;
        //! Alias for @ref LD4
        gpio::DigitalOutput& led_blue = LD4;


        // *** Built-in joystick ***
        //! Joystick down signal
        extern gpio::DigitalInput JOY_DOWN;
        //! Alias for @ref JOY_DOWN
        gpio::DigitalInput& joystick_down = JOY_DOWN;

        //! Joystick up signal
        extern gpio::DigitalInput JOY_UP;
        //! Alias for @ref JOY_UP
        gpio::DigitalInput& joystick_up = JOY_UP;

        //! Joystick right signal
        extern gpio::DigitalInput JOY_RIGHT;
        //! Alias for @ref JOY_RIGHT
        gpio::DigitalInput& joystick_right = JOY_RIGHT;

        //! Joystick left signal
        extern gpio::DigitalInput JOY_LEFT;
        //! Alias for @ref JOY_LEFT
        gpio::DigitalInput& joystick_left = JOY_LEFT;

        //! Joystick select signal
        extern gpio::DigitalInput JOY_SEL;
        //! Alias for @ref JOY_SEL
        gpio::DigitalInput& joystick_selection = JOY_SEL;

        //! Arduino connector of the 32F412GDISCOVERY
        namespace arduino {
            //! Arduino connector analog pin A0
            gpio::__GPIO_Pin& A0 = gpio::PA1;
            //! Arduino connector analog pin A1
            gpio::__GPIO_Pin& A1 = gpio::PC1;
            //! Arduino connector analog pin A2
            gpio::__GPIO_Pin& A2 = gpio::PC3;
            //! Arduino connector analog pin A3
            gpio::__GPIO_Pin& A3 = gpio::PC4;
            //! Arduino connector analog pin A4
            gpio::__GPIO_Pin& A4 = gpio::PC5;
            //! Arduino connector analog pin A5
            gpio::__GPIO_Pin& A5 = gpio::PB0;

            //! Arduino connector digital pin D0
            gpio::__GPIO_Pin& D0 = gpio::PG9;
            //! Arduino connector digital pin D1
            gpio::__GPIO_Pin& D1 = gpio::PG14;
            //! Arduino connector digital pin D2
            gpio::__GPIO_Pin& D2 = gpio::PG13;
            //! Arduino connector digital pin D3
            gpio::__GPIO_Pin& D3 = gpio::PF4;
            //! Arduino connector digital pin D4
            gpio::__GPIO_Pin& D4 = gpio::PG12;
            //! Arduino connector digital pin D5
            gpio::__GPIO_Pin& D5 = gpio::PF10;
            //! Arduino connector digital pin D6
            gpio::__GPIO_Pin& D6 = gpio::PF3;
            //! Arduino connector digital pin D7
            gpio::__GPIO_Pin& D7 = gpio::PG11;
            //! Arduino connector digital pin D8
            gpio::__GPIO_Pin& D8 = gpio::PG10;
            //! Arduino connector digital pin D9
            gpio::__GPIO_Pin& D9 = gpio::PB8;
            //! Arduino connector digital pin D10
            gpio::__GPIO_Pin& D10 = gpio::PA15;
            //! Arduino connector digital pin D11
            gpio::__GPIO_Pin& D11 = gpio::PA7;
            //! Arduino connector digital pin D12
            gpio::__GPIO_Pin& D12 = gpio::PA6;
            //! Arduino connector digital pin D13
            gpio::__GPIO_Pin& D13 = gpio::PA5;
            //! Arduino connector digital pin D14
            gpio::__GPIO_Pin& D14 = gpio::PB9;
            //! Arduino connector digital pin D15
            gpio::__GPIO_Pin& D15 = gpio::PB10;
        }
    }
}

#endif /* LIBEMBED_BSP_DISCO_F412ZG_H_ */