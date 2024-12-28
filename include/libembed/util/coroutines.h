/**
 * @file coroutines.h
 * @author Gabriel Heinzer
 * @brief C++ coroutine implementation allowing for coroutine-specific stack memory.
 */

#include <setjmp.h>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <any>
#include <stdint.h>
#include <libembed/config.h>

#ifndef COROUTINES_HPP_
#define COROUTINES_HPP_

#if LIBEMBED_CONFIG_ENABLE_COROUTINES == true

/**
 * @brief Yield the current coroutine. This can also be used in child functions.
 * You can also use this if aren't sure if you are running in a coroutine; this
 * won't fail if you are not running in a coroutine.
 */
#define yield coroutines::__yield()

/**
 * @brief C++ coroutines implementation. Check @ref coroutines.h for more information.
 * 
 */
namespace embed::coroutines {
    /**
     * @brief Enter the coroutine scheduler. This function should never return,
     * so make sure that you have started at least one coroutine which will then
     * continue with the execution of your program.
     */
    void enterScheduler();

    /**
     * @brief Internal function for yielding the current coroutine.
     * Use the @ref yield macro instead of directly calling this.
     */
    void __yield();

    /**
     * @internal
     * @brief Internal function for getting the stack pointer.
     * 
     * @return Returns the current stack pointer as an `uint8_t*`.
     */
    uint8_t* __getStackPointer();
    /**
     * @internal
     * @brief Internal function for adding two stack pointers together
     * to form the stack pointer to the larger-size stack. For a
     * down-growing stack, this will subtract @p offset from @p sp; for
     * upward-groing stacks, this will add the two parameters.
     * 
     * @param sp The stack pointer you want to manipulate.
     * @param offset The operand of the manipulation.
     * @return Returns the newly calculated stack pointer without modifying the
     * original @p sp variable.
     */
    uint8_t* __addStackPointer(uint8_t* sp, size_t offset);

    // Pre-declaration of the Coroutine class
    struct Coroutine;

    /**
     * @brief Entry point function to a coroutine. This takes
     * two arguments:
     *  - The @ref Coroutine object (by reference) of the parent coroutine
     *  - The argument passed to the constructor of the @ref Coroutine as `std::any`
     */
    typedef void (*CoroutineEntryPoint_t)(Coroutine&, std::any);

    /**
     * @brief Represents a coroutine. Refer to the constructor for more information.
     * 
     */
    class Coroutine
    {
        private:
            /**
             * @brief `setjmp`-buffer called when yielding (enters the scheduler).
             */
            jmp_buf yieldBuf_;
            /**
             * @brief `setjmp`-buffer called when resuming execution.
             */
            jmp_buf resumeBuf_;
            
            /**
             * @brief Stack pointer for this coroutine.
             */
            uint8_t* coroutineStackPtr_;

            /**
             * @brief Specifies if the coroutines stack has already been allocated
             * internally or not.
             */
            bool stackAllocated_ = false;

            /**
             * @brief Runs the coroutine from the specified coroutine with
             * the calculated stack pointer. This is architecture-specific
             * as it involves assembly calls.
             */
            void runFromEntryPoint_();

        public:
            /**
             * @brief The entry point for the coroutine.
             */
            const CoroutineEntryPoint_t entryPoint;
            /**
             * @brief The name of the coroutine.
             */
            const std::string name;
            /**
             * @brief The stack size of the coroutine.
             */
            const size_t stackSize;
            /**
             * @brief Entry point argument given to the constructor.
             */
            const std::any entryPointArgument;
            /**
             * @brief Specifies if the coroutine is currently running. This
             * has nothing to do with the coroutine having yielded or not,
             * but purely with @ref start() and @ref stop() being called or
             * the entry point function returning.
             */
            bool isRunning = false;

            /**
             * @brief Construct a new Coroutine object.
             * 
             * @param entryPoint Entry point function of the coroutine.
             * @param stackSize Stack size of the coroutine. Note that if the coroutine
             * exceeds the stack size, unpredictable things will happen.
             * @param entryPointArgument Argument to pass to the entry point.
             * @param name Name of the coroutine (for debugging purposes).
             */
            Coroutine(CoroutineEntryPoint_t entryPoint, size_t stackSize, std::any entryPointArgument = NULL, const std::string name = "<unknown>");

            /**
             * @internal
             * @brief Internal function for yielding the coroutine.
             * Do not call this directly, use the @ref yield macro instead.
             */
            void __yield();
            /**
             * @internal
             * @brief Start the coroutine if it is not already running,
             * or resume it's execution.
             */
            void __start_or_resume();

            /**
             * @brief Schedule the coroutine for being started.
             */
            void start();
            /**
             * @brief Remove the coroutine from the scheduler.
             * The coroutine will not be resumed anymore, but it will
             * continue it's execution until yielding or returning.
             */
            void stop();
    };
}

#else

#define yield

#endif /* LIBEMBED_ENABLE_COROUTINES == true */

#endif /* COROUTINES_HPP_ */