#include <libembed/util/coroutines.h>
#include <libembed/hal/clock/types.h>
#include <libembed/arch/arm/stm32/stm32_hal.h>

#if LIBEMBED_PLATFORM == ststm32

using namespace embed;

void clock::init() {
    HAL_Init();
}

void clock::delay(int milliseconds) {
    int endTick = HAL_GetTick() + milliseconds;
    while(HAL_GetTick() < endTick) yield;
}

extern "C" void SysTick_Handler() { HAL_IncTick(); }

#endif