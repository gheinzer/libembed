#include <libembed/hal/clock.h>
#include <libembed/util/coroutines.h>
#include <libembed/bsp/autobsp.h>

using namespace embed;

// Entry point for the blinker coroutines
void blinker(gpio::DigitalOutput& output, int interval);

// Blinker coroutines
coroutines::Coroutine<64> greenBlinker{ blinker, board::led_green, 300 };
coroutines::Coroutine<64> orangeBlinker{ blinker, board::led_orange, 400 };

int main() {
    // Initialize the clock HAL
    clock::init();

    // Start both coroutines
    greenBlinker.start();
    orangeBlinker.start();

    // Enter the coroutine scheduler
    coroutines::enterScheduler();
}

void blinker(gpio::DigitalOutput& output, int interval) {
    while(1) {
        // Toggle the output
        output.toggle();

        // Delay the coroutine for the given interval
        clock::delay(interval);
    }
}