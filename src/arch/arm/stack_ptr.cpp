/**
 * @file stack_ptr.cpp
 * @author Gabriel Heinzer
 * @brief Stack-pointer specific implementations for ARM.
 */

#include <libembed/util/coroutines.h>
#include <libembed/config.h>
#include <libembed/util/debug.h>

#if defined(__ARM_ARCH) && LIBEMBED_CONFIG_ENABLE_COROUTINES == true

uint8_t* embed::coroutines::__getStackPointer() {
    uint8_t* sp;
    asm("mov %[stackptr],sp" : [stackptr] "=r" (sp));
    return sp;
}

void embed::coroutines::Coroutine_Base::runFromEntryPoint_() {
    // Clear the stack
    this->stackAllocatorPtr_->clear();

    // Set the stack pointer for the coroutine context
    asm(
        R"(
            mov sp,%[stackptr]
        )" :: [stackptr] "r" (stackAllocatorPtr_->stackEnd)
    );

    // Call the coroutine entry point
    this->callEntryPoint_();
}

#endif