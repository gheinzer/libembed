#include <libembed/util/coroutines.h>

#ifdef __ARM_ARCH

uint8_t* embed::coroutines::__getStackPointer() {
    uint8_t* sp;
    asm("mov %[stackptr],sp" : [stackptr] "=r" (sp));
    return sp;
}
void embed::coroutines::__setStackPointer(uint8_t* sp) {
    asm("mov sp,%[stackptr]" :: [stackptr] "r" (sp));
}

#endif