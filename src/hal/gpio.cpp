#include <libembed/hal/gpio.h>

using namespace embed;

gpio::DigitalOutput::DigitalOutput(gpio::GPIO_Pin& pin, bool inverted, bool initialState, gpio::GPIO_Flag flags) : initialState(initialState), inverted(inverted), flags(flags), gpio(pin) {
    init_specific_();
    write(initialState);
}
gpio::DigitalOutput::DigitalOutput(GPIO_Pin& pin, bool inverted, GPIO_Flag flags) : DigitalOutput(pin, inverted, false, flags) { }
gpio::DigitalOutput::DigitalOutput(GPIO_Pin& pin, GPIO_Flag flags) : DigitalOutput(pin, false, false, flags) {}

void gpio::DigitalOutput::write(bool state) {
    write_specific_(inverted ? !state : state);
}

bool gpio::DigitalOutput::read() {
    return inverted ? !read_specific_() : read_specific_();
}

void gpio::DigitalOutput::disable() { write(false); }
void gpio::DigitalOutput::enable() { write(true); }
void gpio::DigitalOutput::toggle() { toggle_specific_(); }

gpio::DigitalInput::DigitalInput(GPIO_Pin& pin, bool inverted, GPIO_Flag flags) : inverted(inverted), flags(flags), gpio(pin), edge(*this) {
    init_specific_();
}

gpio::DigitalInput::DigitalInput(GPIO_Pin& pin, GPIO_Flag flags) : DigitalInput(pin, false, flags) { }

bool gpio::DigitalInput::read() {
    return inverted ? !read_specific_() : read_specific_();
}

gpio::AnalogInput::AnalogInput(AnalogInput_Pin& pin) : pin(pin) {
    init_specific_();
}

double gpio::AnalogInput::read() {
    return read_specific_();
}