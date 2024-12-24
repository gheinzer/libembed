#include <stdint.h>

#ifndef LIBEMBED_HAL_GPIO_HPP_
#define LIBEMBED_HAL_GPIO_HPP_

namespace embed::gpio {
    void init();

    /**
     * @brief Opaque data structure defining a hardware pin.
     */
    typedef struct __GPIO_Pin GPIO_Pin;

    typedef struct __GPIO_Flags GPIO_Flags;

    class __DigitalOutput_Base {        
        public:
            virtual void write(bool state);
            virtual void toggle();
            virtual void enable();
            virtual void disable();
    };

    class __DigitalInput_Base {
        public:
            virtual bool read();
    };
}

#endif /* LIBEMBED_HAL_GPIO_HPP_ */