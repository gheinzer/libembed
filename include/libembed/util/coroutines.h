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
#include <memory>
#include <functional>
#include <stdint.h>
#include <setjmp.h>
#include <libembed/config.h>
#include <libembed/util/debug.h>

#ifndef COROUTINES_HPP_
#define COROUTINES_HPP_

#if LIBEMBED_CONFIG_ENABLE_COROUTINES == true || defined(__DOXYGEN__)

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

        // Pre-declaration of the Coroutine_Base class
        struct Coroutine_Base;

        /**
         * @brief Pointer to the current coroutine.
         */
        extern Coroutine_Base* current;

        /**
         * @brief Base interface of a stack allocator containing a pointer to the
         * beginning and a pointer to the end of the stack.
         * 
         */
        class StackAllocatorInterface {
            public:
                /**
                 * @brief Points to the first element of the stack.
                 * 
                 */
                uint8_t* stackStart;
                /**
                 * @brief Points to the last element of the stack.
                 * 
                 */
                uint8_t* stackEnd;

                /**
                 * @brief Clears the stack and sets all bytes to 0.
                 * 
                 */
                virtual void clear() = 0;
        };

        /**
         * @brief Template class for a stack allocator.
         * 
         * @tparam stackSize The desired stack size.
         */
        template<std::size_t stackSize> class StackAllocator : public StackAllocatorInterface {
            private:
                /**
                 * @brief Internal stack array for memory allocation.
                 * 
                 */
                uint8_t stack_[stackSize];

            public:
                /**
                 * @brief Construct a new Stack Allocator.
                 * 
                 */
                StackAllocator() {
                    clear();
                    stackStart = stack_;
                    stackEnd = stackStart + stackSize - 1;
                }

                void clear() override {
                    std::fill_n(stack_, stackSize, 0);
                }
        };

        /**
         * @brief Base class for a coroutine. Refer to the constructor for more information.
         * 
         */
        class Coroutine_Base
        {
            protected:
                /**
                 * @brief `setjmp`-buffer called when yielding (enters the scheduler).
                 */
                jmp_buf yieldBuf_;
                /**
                 * @brief `setjmp`-buffer called when resuming execution.
                 */
                jmp_buf resumeBuf_;

                /**
                 * @brief Specifies if the entry point has been called yet.
                 */
                bool wasCalled_ = false;

                /**
                 * @brief Runs the coroutine from the specified coroutine with
                 * the calculated stack pointer. This is architecture-specific
                 * as it involves assembly calls.
                 */
                void runFromEntryPoint_();

                /**
                 * @brief Calls the entry point and also handles any errors in
                 * the entry point.
                 */
                void callEntryPoint_();

                /**
                 * @brief Stack allocator for allocating the coroutine's stack.
                 * This is stored as a shared_ptr so the stack allocator can be allocated
                 * on the stack.
                 */
                std::shared_ptr<StackAllocatorInterface> stackAllocatorPtr_;

            protected:
                /**
                 * @brief Construct a new Coroutine_Base object.
                 * 
                 * @note This constructor is `protected` to prevent instantiation of this base class.
                 * 
                 * @param stackSize Stack size of the coroutine. Note that if the coroutine
                 * exceeds the stack size, unpredictable things will happen.
                 */
                Coroutine_Base(size_t stackSize);

                /**
                 * @brief Destroy the @ref Coroutine_Base object
                 * and stop all running coroutines.
                 */
                ~Coroutine_Base();

                /**
                 * @brief Lambda function for calling the entry point with the given arguments.
                 * 
                 * Implemented in the template class @ref Coroutine.
                 */
                std::function<void()> entryPointCaller_;

            public:
                /**
                 * @brief The stack size of the coroutine.
                 */
                const size_t stackSize;
                /**
                 * @brief Specifies if the coroutine is currently active. This
                 * has nothing to do with the coroutine having yielded or not,
                 * but purely with @ref start() and @ref stop() being called or
                 * the entry point function returning.
                 * 
                 * @see
                 * - @ref start()
                 * - @ref stop()
                 */
                bool isActive = false;
                /**
                 * @brief Specifies if the currently is currently paused or
                 * not.
                 * 
                 * @see
                 *  - @ref pause()
                 *  - @ref resume()
                 */
                bool isPaused = false;
                
                #if LIBEMBED_CONFIG_ENABLE_DEBUGGING
                    /**
                     * @brief Coroutine name (for debugging purposes).
                     */
                    std::string name = "<unknown>";
                #endif /* LIBEMBED_CONFIG_ENABLE_DEBUGGING */

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

                /**
                 * @brief Blocks the calling coroutine until the target coroutine has returned.
                 */
                void join();

                /**
                 * @brief Pause a running coroutine.
                 * @see 
                 *  - @ref resume()
                 */
                void pause();

                /**
                 * @brief Resume a paused coroutine.
                 * @see
                 *  - @ref pause
                 */
                void resume();

                /**
                 * @brief Toggles the coroutines pause state, i.e. pauses
                 * it if it is running or resumes it if it is paused.
                 * 
                 * @see
                 *  - @ref pause()
                 *  - @ref resume()
                 */
                void togglePause();
        };

        /**
         * @brief Template class for a coroutine.
         * 
         * @tparam tmpl_stackSize The size of the stack you want the coroutine to have. Make this large
         * enough to prevent a stack overflow.
         */
        template<size_t tmpl_stackSize> class Coroutine : public Coroutine_Base {
            public:
                /**
                 * @brief Construct a new Coroutine object.
                 * 
                 * Example usage:
                 * @code{.cpp}
                 * void entryPoint(int arg1, int arg2) { ... }
                 * Coroutine<64> blinker{ entryPoint, 10, 20 };
                 * @endcode
                 * 
                 * @tparam tmpl_entryPoint_t Type of the entry point.
                 * @tparam tmpl_entryPointArgs_t Types of the entry point arguments.
                 * 
                 * @param entryPoint Entry point of the coroutine.
                 * @param entryPointArgs Variadic arguments to pass to the entry point.
                 */
                template<typename tmpl_entryPoint_t, typename... tmpl_entryPointArgs_t>
                Coroutine(tmpl_entryPoint_t&& entryPoint, tmpl_entryPointArgs_t&&... entryPointArgs) 
                    : Coroutine_Base(tmpl_stackSize)
                {
                    stackAllocatorPtr_ = std::make_shared<StackAllocator<tmpl_stackSize>>();
                    typedef std::tuple<tmpl_entryPointArgs_t...> args_tuple;

                    // The arguments and the entry point must be passed by value because
                    // of the context switch
                    args_tuple args(std::forward<tmpl_entryPointArgs_t>(entryPointArgs)...);

                    entryPointCaller_ = [args_tpl=args, ep=entryPoint] {
                        ep(std::get<tmpl_entryPointArgs_t>(args_tpl)...);
                    };
                };
        };
    }

#else

    /**
     * @brief Yield macro placeholder. This expands to nothing when
     * coroutines are disabled. For further information, please refer to
     * @ref LIBEMBED_CONFIG_ENABLE_COROUTINES.
     * 
     */
    #define yield

#endif /* LIBEMBED_CONFIG_ENABLE_COROUTINES == true */

// *** Configuration-independent declarations ***
namespace embed::coroutines {
    /**
     * @brief Coroutine-safe lock class.
     * 
     * This is also available if coroutines are disabled.
     */
    class Lock {
        private:
            #if LIBEMBED_CONFIG_ENABLE_COROUTINES
                //! Internal lock state variable
                bool locked_ = false;
            #endif

        public:
            /**
             * @brief Wait for the lock to be released, if it is not already,
             * and acquire it.
             * 
             * If the lock is not released yet, this yields the
             * current coroutine.
             */
            void acquire();

            /**
             * @brief Release the lock for another process to use.
             * 
             * This yields the current coroutine after releasing the lock.
             * 
             * @see
             *  - @ref release_noyield()
             */
            void release();

            /**
             * @brief Releases the lock for another process to use without yielding.
             * 
             * In contrast to @ref release, this does not yield the current
             * coroutine after unlocking.
             * 
             * @see
             * - @ref release()
             */
            void release_noyield();
    };
}

#endif /* COROUTINES_HPP_ */