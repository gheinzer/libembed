#include <setjmp.h>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <any>

#ifndef COROUTINES_HPP_
#define COROUTINES_HPP_

#define yield coroutines::__yield()

#define SCHEDULER_STACK_MARGIN 1024

namespace embed::coroutines {
    void enterScheduler();
    void __yield();

    uint8_t* __getStackPointer();
    uint8_t* __addStackPointer(uint8_t* sp, size_t offset);

    // Pre-declaration of the Coroutine class
    struct Coroutine;

    typedef void (*CoroutineEntryPoint_t)(Coroutine&, std::any);

    class Coroutine
    {
        private:
            jmp_buf yieldBuf_;
            jmp_buf resumeBuf_;
            
            uint8_t* coroutineStackPtr_;

            bool stackAllocated_ = false;

            void runFromEntryPoint_();

        public:
            const CoroutineEntryPoint_t entryPoint;
            const std::string name;
            const size_t stackSize;
            const std::any entryPointArgument;
            bool isRunning = false;

            Coroutine(CoroutineEntryPoint_t entryPoint, size_t stackSize, std::any entryPointArgument, const std::string name = "<unknown>");

            void __yield();
            void __start_or_resume();

            void start();
            void stop();
    };
}


#endif /* COROUTINES_HPP_ */