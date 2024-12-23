#include <libembed/util/util.hpp>
#include <libembed/hal/stm32_hal.h>

using namespace embd;

void util::init() {
    HAL_Init();
}

void util::delay(uint32_t delay) { HAL_Delay(delay); }

extern "C" void SysTick_Handler(void) { HAL_IncTick(); }