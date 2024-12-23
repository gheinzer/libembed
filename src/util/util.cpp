#include <ghcl/util/util.hpp>
#include <ghcl/hal/stm32_hal.h>

using namespace ghcl;

void util::init() {
    HAL_Init();
}

void util::delay(uint32_t delay) { HAL_Delay(delay); }

extern "C" void SysTick_Handler(void) { HAL_IncTick(); }