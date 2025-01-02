/**
 * @file debug.h
 * @author Gabriel Heinzer
 * @brief Debugging utility with no performance overhead when disabling debugging.
 */

#include <libembed/config.h>
#include <libembed/util/macros.h>
#include <string>

#ifndef LIBEMBED_DEBUG_H_
#define LIBEMBED_DEBUG_H_

#if LIBEMBED_CONFIG_ENABLE_DEBUGGING == true

#if LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_INFO == true
    #define libembed_debug_info(message) embed::debug::info(message, __func__);
#endif
#if LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_TRACE == true
    #define libembed_debug_trace(message) embed::debug::trace(message);
#endif

namespace embed::debug {
    extern void (*writeStringPtr)(std::string);

    void info(std::string message, std::string functionName);
    void trace(std::string message, std::string functionName);
};

#else

/**
 * @brief Prints a debug message with the level `INFO`.
 * 
 * @param message The message to print.
 */
#define libembed_debug_info(message)

/**
 * @brief Prints a debug message with the level `TRACE`.
 * 
 * @param message The message to print.
 */
#define libembed_debug_trace(message)

#endif /* LIBEMBED_CONFIG_ENABLE_DEBUGGING */

#endif /* LIBEMBED_DEBUG_H_ */