#include <libembed/util/exceptions.h>
#include <libembed/util/debug.h>

using namespace embed;

bool exceptions::__throwTarget = false;
jmp_buf* exceptions::__current_jmp_buf;
exceptions::exception exceptions::__currentException("<none>");
int exceptions::__setjmpRetVal;

static void __rootExceptionHandler() {
    libembed_debug_info("Uncaught exception: " + std::string(exceptions::__currentException.message));
    while(1);
}

void exceptions::throw_exception(exception exception) {
    exceptions::__currentException = exception;
    if(exceptions::__throwTarget) {
        longjmp(*(exceptions::__current_jmp_buf), 1);
    } else {
        __rootExceptionHandler();
    }
}

exceptions::exception exceptions::current_exception() {
    return exceptions::__currentException;
}