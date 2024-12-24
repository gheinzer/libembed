#include <libembed/util/coroutines.h>
#include <libembed/hal/vcp_serial.h>
#include <vector>

using namespace embd;

// *** Global variables ***
static std::vector<coroutines::Context> activeContexts_ = {};

// *** Root namespace members ***
std::any coroutines::__dummy_variable;

void coroutines::startScheduler() {
    while(1) {
        for(int i = 0; i < activeContexts_.size(); i++) {
            activeContexts_[i].__start_or_resume();
        }
    }
}

// *** coroutines::Coroutine class ***
coroutines::Coroutine::Coroutine(CoroutineEntryPoint_t entryPoint, const std::string name) : entryPoint(entryPoint), name(name) {}

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
coroutines::Context::Context(Coroutine* coroutine, void* entryPointArgument) : coroutine(coroutine) {
    entryPointArgument_ = entryPointArgument;
    hasYielded = false;
}

bool coroutines::Context::__yielded_here(std::string file, std::string function) {
    return yieldFile_ == file && yieldFunction_ == function && hasYielded;
}

void coroutines::Context::__yield(std::string file, std::string function, void* label) {
    yieldFile_ = file;
    yieldFunction_ = function;
    yieldLabel = label;
    hasYielded = true;
    
    longjmp(yieldBuf_, 1);
}

void coroutines::Context::__start_or_resume() {
    volatile int sjVal = setjmp(yieldBuf_);
    if(sjVal == 0) {
        coroutine->entryPoint(*this, entryPointArgument_);
    }
}