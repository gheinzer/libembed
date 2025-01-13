#include <libembed/util/coroutines.h>
#include <libembed/util/debug.h>
#include <libembed/util/exceptions.h>
#include <libembed/config.h>
#include <vector>
#include <algorithm>

using namespace embed;

#if LIBEMBED_CONFIG_ENABLE_COROUTINES == true

#define NO_COROUTINE SIZE_MAX
#define SCHEDULER_STACK_MARGIN 256

// *** Global variables ***
static std::vector<coroutines::Coroutine_Base*> activeCoroutines_ = {};
static uint8_t* coroutineStackEndPtr_;
static size_t currentContext_ = NO_COROUTINE;

coroutines::Coroutine_Base* coroutines::current;

static void __initStackPointer() {
    coroutineStackEndPtr_ = coroutines::__addStackPointer(coroutines::__getStackPointer(), SCHEDULER_STACK_MARGIN);
}

void coroutines::enterScheduler() {
    __initStackPointer();
    libembed_debug_info("Entering coroutine scheduler...");
    while(1) {
        for(currentContext_ = 0; currentContext_ < activeCoroutines_.size(); currentContext_++) {
            embed::coroutines::current = activeCoroutines_[currentContext_];
            
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
coroutines::Coroutine_Base::Coroutine_Base(size_t stackSize) : stackSize(stackSize) {
}

coroutines::Coroutine_Base::~Coroutine_Base() {
    stop();
}

void coroutines::Coroutine_Base::start() {
    if(!isActive) {
        activeCoroutines_.push_back(this);
        isActive = true;
        isPaused = false;
        libembed_debug_trace("Coroutine " + name + " started.");
    }
}

void coroutines::Coroutine_Base::stop() {
    activeCoroutines_.erase(std::remove(activeCoroutines_.begin(), activeCoroutines_.end(), this), activeCoroutines_.end());
    isActive = false;
    wasCalled_ = false;
    isPaused = false;
    libembed_debug_trace("Coroutine " + name + " stopped.");
}

void coroutines::Coroutine_Base::pause() {
    if(isActive)
        isPaused = true;
}

void coroutines::Coroutine_Base::resume() {
    if(isActive)
        isPaused = false;
}

void coroutines::Coroutine_Base::togglePause() {
    isPaused ? resume() : pause();
}

void coroutines::Coroutine_Base::__yield() {
    if(!setjmp(resumeBuf_)) {
        longjmp(yieldBuf_, 1); // Jump back to the scheduler
    }
}

void coroutines::Coroutine_Base::__start_or_resume() {
    if(isPaused) return; // Don't resume if the coroutine is currently paused
    if(!setjmp(yieldBuf_)) {
        libembed_debug_trace("Coroutine " + name + " resumed.");
        if(!wasCalled_) {
            wasCalled_ = true;
            libembed_try {
                runFromEntryPoint_();
            } libembed_catch {
                libembed_debug_info("Coroutine " + name + " threw an error.")                
            }
        } else {
            longjmp(resumeBuf_, 1); // Jump into the execution
        }
    } else {
        libembed_debug_trace("Coroutine " + name + " yielded.");
    }
}

void coroutines::Coroutine_Base::join() {
    while(isActive) yield;
}

void coroutines::Lock::acquire() {
    while(locked_) yield;
    locked_ = true;
}

void coroutines::Lock::release() {
    release_noyield();
    yield;
}

void coroutines::Lock::release_noyield() {
    locked_ = false;
}

#else

void coroutines::Lock::acquire() { }

void coroutines::Lock::release() { }

void coroutines::Lock::release_noyield() { }

#endif