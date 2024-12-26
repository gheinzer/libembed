#include <libembed/util/coroutines.h>
#include <vector>

using namespace embed;

// *** Global variables ***
static std::vector<coroutines::Context> activeContexts_ = {};
static uint8_t* coroutineStackEndPtr_;

// *** Root namespace members ***
std::any coroutines::__dummy_variable;

void coroutines::enterScheduler() {
    coroutineStackEndPtr_ = coroutines::__getStackPointer() + SCHEDULER_STACK_MARGIN;
    while(1) {
        for(int i = 0; i < activeContexts_.size(); i++) {
            activeContexts_[i].__start_or_resume();
        }
    }
}

// *** coroutines::Coroutine class ***
coroutines::Coroutine::Coroutine(CoroutineEntryPoint_t entryPoint, size_t stackSize, const std::string name) : entryPoint(entryPoint), name(name), stackSize(stackSize) {}

void coroutines::Coroutine::start(void* argument) {
    Context ctxt(this, argument);
    activeContexts_.push_back(ctxt);
}

void coroutines::Coroutine::stopAll() {
    for(int i = 0; i < activeContexts_.size(); i++) {
        if(activeContexts_.at(i).coroutine == this) {
            activeContexts_.erase(activeContexts_.begin() + i);
        }
    }
}

// *** coroutines::Context  class***
coroutines::Context::Context(Coroutine* coroutine, void* entryPointArgument) : coroutine(coroutine), entryPointArgument_(entryPointArgument) {}

void coroutines::Context::__yield() {
    if(setjmp(resumeBuf_)) {
        longjmp(yieldBuf_, 1); // Jump back to the scheduler
    }
}

void coroutines::Context::__start_or_resume() {
    if(setjmp(yieldBuf_)) {
        if(!isRunning_) {
            coroutineStackPtr_ = coroutineStackEndPtr_;
            coroutineStackEndPtr_ += coroutine->stackSize;
            coroutines::__setStackPointer(coroutineStackPtr_);
            isRunning_ = true;
            coroutine->entryPoint(*this, entryPointArgument_);
            isRunning_ = false;

            // TODO: DO SOMETHING TO STOP THE COROUTINE
        } else {
            longjmp(resumeBuf_, 1); // Jump into the execution
        }
    }
}