#include <setjmp.h>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <any>

#ifndef COROUTINES_HPP_
#define COROUTINES_HPP_

#define yield threading::__yield()

#define __COROUTINE_CONCAT2_(a, b) a##b
#define __COROUTINE_CONCAT2(a, b) __COROUTINE_CONCAT2_(a, b)
#define __COROUTINE_YIELDLABEL __COROUTINE_CONCAT2(__yield_label, __LINE__)

#define coroutine_begin(__coroutine_context) \
    coroutine_declare(__coroutine_context, uint32_t, __coroutine_delay_counter, 0); \
    if(__coroutine_context.__yielded_here(__FILE__, __func__)) { \
        goto *__coroutine_context.yieldLabel; \
    }
    
#define coroutine_declare(__coroutine_context, __lvar_type, __lvar_name, __lvar_initialValue) \
    __lvar_type& __lvar_name = __coroutine_context.__getVariable<__lvar_type>(__COUNTER__, (__lvar_initialValue));

#define coroutine_yield(__coroutine_context) \
    __coroutine_context.__yield(__FILE__, __func__, &&__COROUTINE_YIELDLABEL); \
    __COROUTINE_YIELDLABEL:

#define coroutine_delay(__coroutine_context, __delay_ms) \
    __coroutine_delay_counter = HAL_GetTick() + (__delay_ms); \
    while(HAL_GetTick() < __coroutine_delay_counter) { coroutine_yield(__coroutine_context); }

namespace ghcl::coroutines {
    void startScheduler();

    struct Coroutine; // Pre-declaration of the Coroutine class

    class Context {
        private:
            std::map<unsigned int, std::any> contextVariables_;
            std::string yieldFile_;
            std::string yieldFunction_;
            void* entryPointArgument_;
            jmp_buf yieldBuf_;
            jmp_buf resumeBuf_;
    
        public:
            Context(Coroutine* coroutine, void* entryPointArgument);

            void* yieldLabel;
            bool hasYielded;

            bool __yielded_here(std::string file, std::string function);
            void __yield(std::string file, std::string function, void* label);
            void __start_or_resume();

            Coroutine* coroutine;

            template<typename T> T& __getVariable(unsigned int id) {
                T initVal{};
                return __getVariable<T>(id, initVal);
            }

            template<typename T> T& __getVariable(unsigned int id, T initVal) {
                if(contextVariables_.find(id) == contextVariables_.end()) {
                    contextVariables_[id] = initVal;
                }
                std::any& anyVal = contextVariables_[id];
                T* val = std::any_cast<T>(&anyVal);
                return *val;
            }
    };

    typedef void (*CoroutineEntryPoint_t)(Context&, void*);

    class Coroutine
    {
        public:
            const CoroutineEntryPoint_t entryPoint;
            const std::string name;

            Coroutine(CoroutineEntryPoint_t entryPoint, const std::string name = "<unknown>");

            void start(void* argument = 0);
            void stopAll();
    };

    extern std::any __dummy_variable;
}


#endif /* COROUTINES_HPP_ */