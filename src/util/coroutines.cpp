#include <libembed/util/coroutines.h>
#include <vector>

using namespace embed;

// *** Global variables ***
static std::vector<coroutines::Coroutine*> activeCoroutines_ = {};
static uint8_t* coroutineStackEndPtr_;
static size_t currentContext_ = 0;

void coroutines::enterScheduler() {
    coroutineStackEndPtr_ = __addStackPointer(__getStackPointer(), SCHEDULER_STACK_MARGIN);
    while(1) {
        for(currentContext_ = 0; currentContext_ < activeCoroutines_.size(); currentContext_++) {
            activeCoroutines_[currentContext_]->__start_or_resume();
        }
    }
}

void coroutines::__yield() {
    activeCoroutines_[currentContext_]->__yield();
}

// *** coroutines::Coroutine class ***
coroutines::Coroutine::Coroutine(CoroutineEntryPoint_t entryPoint, size_t stackSize, std::any entryPointArgument, const std::string name) : entryPoint(entryPoint), name(name), stackSize(stackSize), entryPointArgument(entryPointArgument) {}

void coroutines::Coroutine::start() {
    if(!isRunning)
        activeCoroutines_.push_back(this);
}

void coroutines::Coroutine::stop() {
    for(int i = 0; i < activeCoroutines_.size(); i++) {
        if(activeCoroutines_.at(i) == this) {
            activeCoroutines_.erase(activeCoroutines_.begin() + i);
        }
    }
    isRunning = false;
}

void coroutines::Coroutine::__yield() {
    if(!setjmp(resumeBuf_)) {
        longjmp(yieldBuf_, 1); // Jump back to the scheduler
    }
}

void coroutines::Coroutine::__start_or_resume() {
    if(!setjmp(yieldBuf_)) {
        if(!isRunning) {
            coroutineStackPtr_ = coroutineStackEndPtr_;
            coroutineStackEndPtr_ = __addStackPointer(coroutineStackEndPtr_, stackSize);
            isRunning = true;
            runFromEntryPoint_();
        } else {
            longjmp(resumeBuf_, 1); // Jump into the execution
        }
    }
}