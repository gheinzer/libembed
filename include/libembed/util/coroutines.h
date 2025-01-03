/**
 * @file coroutines.h
 * @author Gabriel Heinzer
 * @brief C++ coroutine implementation allowing for coroutine-specific stack memory.
 * 
 * @example coroutine-blink/main.cpp
 */

#include <setjmp.h>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <any>
#include <memory>
#include <stdint.h>
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
         * @brief A coroutine entry point takes two arguments:
         *  - The @ref Coroutine_Base object (by reference) of the parent coroutine
         *  - The argument passed to the constructor of the @ref Coroutine_Base as `std::any`
         */
        typedef void (*CoroutineEntryPoint_t)(Coroutine_Base&, std::any);

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
                 * @param entryPoint Entry point function of the coroutine.
                 * @param stackSize Stack size of the coroutine. Note that if the coroutine
                 * exceeds the stack size, unpredictable things will happen.
                 * @param entryPointArgument Argument to pass to the entry point.
                 * @param name Name of the coroutine (for debugging purposes).
                 */
                Coroutine_Base(CoroutineEntryPoint_t entryPoint, size_t stackSize, std::any entryPointArgument = NULL, const std::string name = "<unknown>");

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
        };

        /**
         * @brief Template class for a coroutine.
         * 
         * @tparam tmpl_stackSize The size of the stack you want the coroutine to have.
         */
        template<size_t tmpl_stackSize> class Coroutine : public Coroutine_Base {            
            public:
                /**
                 * @brief Construct a new Coroutine object.
                 * 
                 * @param entryPoint Entry point of the coroutine.
                 * @param entryPointArgument Argument to pass to the entry point.
                 * @param name Name of the coroutine for debugging purposes.
                 */
                Coroutine(CoroutineEntryPoint_t entryPoint, std::any entryPointArgument = NULL, const std::string name = "<unknown>") : Coroutine_Base(entryPoint, tmpl_stackSize, entryPointArgument, name) {
                    stackAllocatorPtr_ = std::make_shared<StackAllocator<tmpl_stackSize>>();
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