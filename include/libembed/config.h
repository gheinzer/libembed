/**
 * @file config.h
 * @author Gabriel Heinzer
 * @brief libembed configuration file support.
 * 
 * @note This is the header the library includes for getting the configuration values. If you want to create a configuration file,
 * call it `libembed_config.h` and make sure to include it in your include search path.
 * Undefined configuration values are set to their default values automatically.
 * 
 * @example libembed_config.h
 */

#ifndef LIBEMBED_CONFIG_H_
#define LIBEMBED_CONFIG_H_

#ifndef __DOXYGEN__

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

#endif /* __DOXYGEN__ */

#endif /* LIBEMBED_CONFIG_H_ */