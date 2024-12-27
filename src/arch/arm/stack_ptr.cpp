#include <libembed/util/coroutines.h>

#ifdef __ARM_ARCH

uint8_t* embed::coroutines::__getStackPointer() {
    uint8_t* sp;
    asm("mov %[stackptr],sp" : [stackptr] "=r" (sp));
    return sp;
}

uint8_t* embed::coroutines::__addStackPointer(uint8_t* sp, size_t offset) { return sp - offset; }

void embed::coroutines::Coroutine::runFromEntryPoint_() {
    // Set the stack pointer for the coroutine context
    asm(
        R"(
            mov sp,%[stackptr]
        )" :: [stackptr] "r" (coroutineStackPtr_)
    );

    // Call the coroutine entry point
    this->entryPoint(*this, this->entryPointArgument);
    this->stop();
    longjmp(yieldBuf_, 1);
}

#endif