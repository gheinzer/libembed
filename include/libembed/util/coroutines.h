#include <setjmp.h>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <any>

#ifndef COROUTINES_HPP_
#define COROUTINES_HPP_

#define yield threading::__yield()

#define __COROUTINE_CONCAT2_(a, b) a##b
#define __COROUTINE_CONCAT2(a, b) __COROUTINE_CONCAT2_(a, b)
#define __COROUTINE_YIELDLABEL __COROUTINE_CONCAT2(__yield_label, __LINE__)

#define coroutine_yield(__coroutine_context) \
    __coroutine_context.__yield(__FILE__, __func__); \

#define coroutine_delay(__coroutine_context, __delay_ms) \
    uint32_t __coroutine_delay_counter = HAL_GetTick() + (__delay_ms); \
    while(HAL_GetTick() < __coroutine_delay_counter) { coroutine_yield(__coroutine_context); }

#define SCHEDULER_STACK_MARGIN 1024

namespace embed::coroutines {
    void enterScheduler();

    uint8_t* __getStackPointer();
    void __setStackPointer(uint8_t* sp);

    struct Coroutine; // Pre-declaration of the Coroutine class

    class Context {
        private:
            void* entryPointArgument_;
            jmp_buf yieldBuf_;
            jmp_buf resumeBuf_;
            
            uint8_t* coroutineStackPtr_;

            bool isRunning_ = false;
    
        public:
            Context(Coroutine* coroutine, void* entryPointArgument);

            void __yield();
            void __start_or_resume();

            Coroutine* coroutine;
    };

    typedef void (*CoroutineEntryPoint_t)(Context&, void*);

    class Coroutine
    {
        public:
            const CoroutineEntryPoint_t entryPoint;
            const std::string name;
            const size_t stackSize;

            Coroutine(CoroutineEntryPoint_t entryPoint, size_t stackSize, const std::string name = "<unknown>");

            void start(void* argument = 0);
            void stopAll();
    };

    extern std::any __dummy_variable;
}


#endif /* COROUTINES_HPP_ */