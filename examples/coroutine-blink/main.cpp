#include <libembed/hal/clock.h>
#include <libembed/util/coroutines.h>
#include <libembed/bsp/autobsp.h>

using namespace embed;

// Entry point for the blinker coroutines
void blinker(coroutines::Coroutine_Base& coro, std::any output);

// Blinker coroutines
coroutines::Coroutine<64> greenBlinker(blinker, &board::led_green);
coroutines::Coroutine<64> orangeBlinker(blinker, &board::led_orange);

int main() {
    // Initialize the clock HAL
    clock::init();

    // Start both coroutines
    greenBlinker.start();
    orangeBlinker.start();

    // Enter the coroutine scheduler
    coroutines::enterScheduler();
}

void blinker(coroutines::Coroutine_Base& coro, std::any output) {
    // Cast the std::any argument into a DigitalOutput*
    gpio::DigitalOutput* led_output = std::any_cast<gpio::DigitalOutput*>(output);

    while(1) {
        // Toggle the output
        led_output->toggle();

        // Delay the coroutine for 300 ms
        clock::delay(300);
    }
}