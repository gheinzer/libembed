#include <libembed/util/coroutines.h>
#include <libembed/util/debug.h>
#include <libembed/config.h>
#include <vector>
#include <algorithm>

#if LIBEMBED_CONFIG_ENABLE_COROUTINES == true

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
    libembed_debug_info("Entering coroutine scheduler...");
    while(1) {
        for(currentContext_ = 0; currentContext_ < activeCoroutines_.size(); currentContext_++) {
            libembed_debug_trace("Rescheduling to coroutine " + activeCoroutines_[currentContext_]->name);
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
        libembed_debug_trace("Coroutine " + name + " started.");
    }
}

void coroutines::Coroutine_Base::stop() {
    activeCoroutines_.erase(std::remove(activeCoroutines_.begin(), activeCoroutines_.end(), this), activeCoroutines_.end());
    isRunning = false;
    wasCalled_ = false;
    libembed_debug_trace("Coroutine " + name + " stopped.");
}

void coroutines::Coroutine_Base::__yield() {
    if(!setjmp(resumeBuf_)) {
        longjmp(yieldBuf_, 1); // Jump back to the scheduler
    }
}

void coroutines::Coroutine_Base::__start_or_resume() {
    if(!setjmp(yieldBuf_)) {
        libembed_debug_trace("Coroutine " + name + " resumed.");
        if(!wasCalled_) {
            wasCalled_ = true;
            runFromEntryPoint_();
        } else {
            longjmp(resumeBuf_, 1); // Jump into the execution
        }
    } else {
        libembed_debug_trace("Coroutine " + name + " yielded.");
    }
}

void coroutines::Coroutine_Base::join() {
    while(isRunning) yield;
}

#endif