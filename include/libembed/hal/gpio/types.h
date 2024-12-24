#include <stdint.h>

#ifndef LIBEMBED_HAL_GPIO_HPP_
#define LIBEMBED_HAL_GPIO_HPP_

namespace embed::gpio {
    void init();

    typedef struct GPIO GPIO_t;

    class DigitalOutput {
        private:
            GPIO_t& gpio_;

        public:
            DigitalOutput(GPIO_t& gpio, uint32_t mode);

            void write(bool state);
            void toggle();
            void enable();
            void disable();
    };

    class DigitalInput {
        private:
            GPIO &gpio_;

        public:
            DigitalInput(GPIO &gpio, uint32_t mode);

            bool read();
    };
}

#endif /* LIBEMBED_HAL_GPIO_HPP_ */