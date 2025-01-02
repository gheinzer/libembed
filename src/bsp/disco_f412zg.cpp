#include <libembed/bsp/autobsp.h>

#if LIBEMBED_BOARD_DISCO_F412ZG

    embed::gpio::DigitalOutput embed::board::LD1(gpio::PE0, true);
    embed::gpio::DigitalOutput embed::board::LD2(gpio::PE1, true);
    embed::gpio::DigitalOutput embed::board::LD3(gpio::PE2, true);
    embed::gpio::DigitalOutput embed::board::LD4(gpio::PE3, true);

    embed::gpio::DigitalInput embed::board::JOY_SEL(gpio::PA0, false, gpio::PULLDOWN);
    embed::gpio::DigitalInput embed::board::JOY_DOWN(gpio::PG1, false, gpio::PULLDOWN);
    embed::gpio::DigitalInput embed::board::JOY_LEFT(gpio::PF15, false, gpio::PULLDOWN);
    embed::gpio::DigitalInput embed::board::JOY_RIGHT(gpio::PF14, false, gpio::PULLDOWN);
    embed::gpio::DigitalInput embed::board::JOY_UP(gpio::PG0, false, gpio::PULLDOWN);

    embed::gpio::DigitalOutput& embed::board::led_green = LD1;
    embed::gpio::DigitalOutput& embed::board::led_orange = LD2;
    embed::gpio::DigitalOutput& embed::board::led_red = LD3;
    embed::gpio::DigitalOutput& embed::board::led_blue = LD4;
    embed::gpio::DigitalInput& embed::board::joystick_down = JOY_DOWN;
    embed::gpio::DigitalInput& embed::board::joystick_up = JOY_UP;
    embed::gpio::DigitalInput& embed::board::joystick_right = JOY_RIGHT;
    embed::gpio::DigitalInput& embed::board::joystick_left = JOY_LEFT;
    embed::gpio::DigitalInput& embed::board::joystick_selection = JOY_SEL;

    embed::gpio::__GPIO_Pin& embed::board::arduino::A0 = gpio::PA1;
    embed::gpio::__GPIO_Pin& embed::board::arduino::A1 = gpio::PC1;
    embed::gpio::__GPIO_Pin& embed::board::arduino::A2 = gpio::PC3;
    embed::gpio::__GPIO_Pin& embed::board::arduino::A3 = gpio::PC4;
    embed::gpio::__GPIO_Pin& embed::board::arduino::A4 = gpio::PC5;
    embed::gpio::__GPIO_Pin& embed::board::arduino::A5 = gpio::PB0;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D0 = gpio::PG9;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D1 = gpio::PG14;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D2 = gpio::PG13;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D3 = gpio::PF4;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D4 = gpio::PG12;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D5 = gpio::PF10;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D6 = gpio::PF3;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D7 = gpio::PG11;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D8 = gpio::PG10;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D9 = gpio::PB8;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D10 = gpio::PA15;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D11 = gpio::PA7;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D12 = gpio::PA6;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D13 = gpio::PA5;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D14 = gpio::PB9;
    embed::gpio::__GPIO_Pin& embed::board::arduino::D15 = gpio::PB10;

#endif