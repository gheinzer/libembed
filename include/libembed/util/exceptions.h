/**
 * @file exceptions.h
 * @author Gabriel Heinzer (gabriel.heinzer@roche.com)
 * @brief Lightweight exception handling system using `setjmp`/`longjmp`.
 */

#include <string>
#include <setjmp.h>
#include <typeinfo>

#ifndef LIBEMBED_UTIL_EXCEPTIONS_H_
#define LIBEMBED_UTIL_EXCEPTIONS_H_

/**
 * @brief Try macro for exception handling. Use this
 * in the same way as the normal `try` keyword.
 */
#define libembed_try \
    { \
        jmp_buf* __libembed__exc_previousJmpBuf = embed::exceptions::__current_jmp_buf; \
        jmp_buf __libembed_exc_current_jmp_buf; \
        embed::exceptions::__current_jmp_buf = &__libembed_exc_current_jmp_buf; \
        int __libembed_exc_setjmp_retVal = setjmp(__libembed_exc_current_jmp_buf); \
        bool __libembed_exc_previousThrowTarget = embed::exceptions::__throwTarget; \
        embed::exceptions::__throwTarget = true; \
        if(__libembed_exc_setjmp_retVal == 0)

#define __libembed_close_try \
        embed::exceptions::__current_jmp_buf = __libembed__exc_previousJmpBuf; \
        embed::exceptions::__setjmpRetVal = __libembed_exc_setjmp_retVal; \
        embed::exceptions::__throwTarget = __libembed_exc_previousThrowTarget; \
    }

/**
 * @brief Catch macro for exception handling. Use
 * this without braces. This handles all exceptions.
 */
#define libembed_catch \
    __libembed_close_try; \
    if( \
        embed::exceptions::__setjmpRetVal != 0 \
    )

/**
 * @brief Lightweight exception handling which does not
 * require RTTI or C++ exceptions. Uses `setjmp` and `longjmp`.
 */
namespace embed::exceptions {
    /**
     * @brief Exception class for exception handling using
     * `libembed/util/exceptions.h`.
     */
    class exception {
        public:
            /**
             * @brief Error message passed to the constructor.
             */
            std::string message;

            /**
             * @brief Construct a new exception object.
             * 
             * @param message Error information message.
             */
            exception(std::string message) : message(message) { };
    };

    /**
     * @brief Throws the given `exception`.
     * 
     * @param exception The exception you want to throw.
     */
    [[noreturn]] void throw_exception(exception exception);
    
    /**
     * @brief Gets the current exception.
     * 
     * @return Returns a copy of the current exception.
     */
    exception current_exception();
    
    //! Internal variable specifying the target for `throw_exception`. If this is `true`, `longjmp` is used.
    extern bool __throwTarget;
    //! Internal `jmp_buf` for exception handling.
    extern jmp_buf* __current_jmp_buf;
    //! Internal current exception variable
    extern exception __currentException;
    //! Internal `setjmp` return value variable
    extern int __setjmpRetVal;

    // *** Pre-defined exceptions ***
    /**
     * @brief Thrown when a specified feature is not supported on a device.
     */
    class unsupported_on_this_device : public exception { using exception::exception; };

    /**
     * @brief Thrown when a fatal low-level error has occurred, e.g. a ADC overrun.
     */
    class lowlevel_error : public exception { public: using exception::exception; };
}

#endif /* LIBEMBED_UTIL_EXCEPTIONS_H_ */