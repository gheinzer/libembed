#include <libembed/bsp/autobsp.h>

#if LIBEMBED_BOARD == disco_f412zg

    using namespace embed;
    using namespace embed::board::disco_f412zg;

    gpio::DigitalOutput LD1(gpio::PE0);
    gpio::DigitalOutput LD2(gpio::PE1);
    gpio::DigitalOutput LD3(gpio::PE2);
    gpio::DigitalOutput LD4(gpio::PE3);

    gpio::DigitalInput JOY_SEL(gpio::PA0);
    gpio::DigitalInput JOY_DOWN(gpio::PG1);
    gpio::DigitalInput JOY_LEFT(gpio::PF15);
    gpio::DigitalInput JOY_RIGHT(gpio::PF14);
    gpio::DigitalInput JOY_UP(gpio::PG0);

#endif