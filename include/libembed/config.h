/**
 * @file config.h
 * @author Gabriel Heinzer
 * @brief libembed configuration file support.
 * 
 * @note This is the header the library includes for getting the configuration values. If you want to create a configuration file,
 * call it `libembed_config.h` and make sure to include it in your include search path.
 * Undefined configuration values are set to their default values automatically.
 */

#ifndef LIBEMBED_CONFIG_H_
#define LIBEMBED_CONFIG_H_

#if !defined(__DOXYGEN__)

    #if __has_include(<libembed_config.h>)
        #include <libembed_config.h>
    #else
        #warning You do not seem to have a configuration file for libembed. It is recommended to create a libembed_config.h file for configuration.
    #endif

    #ifndef LIBEMBED_CONFIG_ENABLE_COROUTINES
    #define LIBEMBED_CONFIG_ENABLE_COROUTINES false
    #endif /* LIBEMBED_CONFIG_ENABLE_COROUTINES */

    #ifndef LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT
    #define LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT 1000
    #endif /* LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT */

    #ifndef LIBEMBED_CONFIG_STM32_UART_DEFAULT_RECV_TIMEOUT
    #define LIBEMBED_CONFIG_STM32_UART_DEFAULT_RECV_TIMEOUT 1000
    #endif /* LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT */

    #ifndef LIBEMBED_CONFIG_ENABLE_DEBUGGING
    #define LIBEMBED_CONFIG_ENABLE_DEBUGGING false
    #endif /* LIBEMBED_CONFIG_ENABLE_DEBUGGING */

    #ifndef LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_INFO
    #define LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_INFO true
    #endif /* LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_INFO */

    #ifndef LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_TRACE
    #define LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_TRACE true
    #endif /* LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_TRACE */

    #ifndef LIBEMBED_CONFIG_DEBUG_FUNCTION_NAME_MAXLEN
    #define LIBEMBED_CONFIG_DEBUG_FUNCTION_NAME_MAXLEN 20
    #endif /* LIBEMBED_CONFIG_DEBUG_FUNCTION_NAME_MAXLEN */

#else
    // Doxygen should see all features, independent of the local configuration file
    
    /**
     * @brief Whether to enable `libembed`'s coroutines. 
     * 
     * This also enables coroutine compatibility for blocking library functions (e.g. delay functions).
     * They will yield by default instead of blocking all coroutines.
     * 
     * Set to `true` to enable coroutines, or `false` to disable.
     * 
     * Default value: `false`.
     * 
     * @warning Enabling coroutines may come with a performance and memory penalty.
     */
    #define LIBEMBED_CONFIG_ENABLE_COROUTINES true

    /**
     * @brief Default send timeout for STM32 UART transmissions.
     * 
     * Default value: 1000
     * 
     */
    #define LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT 1000

    /**
     * @brief Default receive timeout for STM32 UART transmissions.
     * 
     * Default value: 1000
     * 
     */
    #define LIBEMBED_CONFIG_RECV_UART_DEFAULT_SEND_TIMEOUT 1000

    /**
     * @brief Enables debugging. Note that this may come with a significant
     * performance overhead.
     * 
     * Default value: `false`
     */
    #define LIBEMBED_CONFIG_ENABLE_DEBUGGING false

    /**
     * @brief Enables the debug level `INFO`.
     * 
     * This is overwritten by @ref LIBEMBED_CONFIG_ENABLE_DEBUGGING.
     * 
     * Default value: `true`
     */
    #define LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_INFO true

    /**
     * @brief Enables the debug level `TRACE`.
     * 
     * This is overwritten by @ref LIBEMBED_CONFIG_ENABLE_DEBUGGING.
     * 
     * Default value: `true`
     */
    #define LIBEMBED_CONFIG_ENABLE_DEBUGLEVEL_TRACE true

    /**
     * @brief Maximum length of the function name for debugging.
     * 
     * The rest will be padded with spaces.
     * 
     * Default value: 20
     */
    #define LIBEMBED_CONFIG_DEBUG_FUNCTION_NAME_MAXLEN 20

#endif /* __DOXYGEN__ */

#endif /* LIBEMBED_CONFIG_H_ */