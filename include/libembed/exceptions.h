/**
 * @file exceptions.h
 * @author Gabriel Heinzer
 * @brief Exceptions for libembed.
 */

#ifndef LIBEMBED_EXCEPTIONS_H_
#define LIBEMBED_EXCEPTIONS_H_

#include <stdexcept>

namespace embed {
    /**
     * @brief Thrown when a specified feature is not supported on a device.
     */
    class unsupported_on_this_device : public std::invalid_argument {        
        public:
            using std::invalid_argument::invalid_argument;
    };
}

#endif /* LIBEMBED_EXCEPTIONS_H_ */