/**
 * @file stack_ptr.cpp
 * @author Gabriel Heinzer
 * @brief Stack-pointer specific implementations for ARM.
 */

#include <libembed/util/coroutines.h>
#include <libembed/config.h>

#if defined(__ARM_ARCH) && LIBEMBED_CONFIG_ENABLE_COROUTINES == true

uint8_t* embed::coroutines::__getStackPointer() {
    uint8_t* sp;
    asm("mov %[stackptr],sp" : [stackptr] "=r" (sp));
    return sp;
}

uint8_t* embed::coroutines::__addStackPointer(uint8_t* sp, size_t offset) { return sp - offset; }

void embed::coroutines::Coroutine_Base::runFromEntryPoint_() {
    // Set the stack pointer for the coroutine context
    asm(
        R"(
            mov sp,%[stackptr]
        )" :: [stackptr] "r" (stackAllocatorPtr_->stackEnd)
    );

    // Call the coroutine entry point
    this->entryPoint(*this, this->entryPointArgument);
    this->stop();
    this->__yield();
}

#endif