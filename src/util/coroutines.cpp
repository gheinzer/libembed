#include <libembed/util/coroutines.h>
#include <vector>

using namespace embed;

#define NO_COROUTINE SIZE_MAX
#define SCHEDULER_STACK_MARGIN 256

// *** Global variables ***
static std::vector<coroutines::Coroutine_Base*> activeCoroutines_ = {};
static uint8_t* coroutineStackEndPtr_;
static size_t currentContext_ = NO_COROUTINE;

static void __initStackPointer() {
    coroutineStackEndPtr_ = coroutines::__addStackPointer(coroutines::__getStackPointer(), SCHEDULER_STACK_MARGIN);
}

void coroutines::enterScheduler() {
    __initStackPointer();
    while(1) {
        for(currentContext_ = 0; currentContext_ < activeCoroutines_.size(); currentContext_++) {
            activeCoroutines_[currentContext_]->__start_or_resume();
        }
    }
}

void coroutines::__yield() {
    if(currentContext_ != NO_COROUTINE)
        activeCoroutines_[currentContext_]->__yield();
}

// *** coroutines::Coroutine_Base class ***
coroutines::Coroutine_Base::Coroutine_Base(CoroutineEntryPoint_t entryPoint, size_t stackSize, std::any entryPointArgument, const std::string name) : entryPoint(entryPoint), name(name), stackSize(stackSize), entryPointArgument(entryPointArgument) {
}

void coroutines::Coroutine_Base::start() {
    if(!isRunning) {
        activeCoroutines_.push_back(this);
        isRunning = true;
    }
}

void coroutines::Coroutine_Base::stop() {
    for(int i = 0; i < activeCoroutines_.size(); i++) {
        if(activeCoroutines_.at(i) == this) {
            activeCoroutines_.erase(activeCoroutines_.begin() + i);
        }
    }
    isRunning = false;
    wasCalled_ = false;
}

void coroutines::Coroutine_Base::__yield() {
    if(!setjmp(resumeBuf_)) {
        longjmp(yieldBuf_, 1); // Jump back to the scheduler
    }
}

void coroutines::Coroutine_Base::__start_or_resume() {
    if(!setjmp(yieldBuf_)) {
        if(!wasCalled_) {
            wasCalled_ = true;
            runFromEntryPoint_();
        } else {
            longjmp(resumeBuf_, 1); // Jump into the execution
        }
    }
}

void coroutines::Coroutine_Base::join() {
    while(isRunning) yield;
}