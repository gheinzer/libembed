/**
 * @file types.h
 * @author Gabriel Heinzer
 * @brief Common type definitions for @ref libembed/hal/uart.h.
 */

#include <stdint.h>
#include <string>
#include <libembed/config.h>

#ifndef LIBEMBED_HAL_UART_TYPES_H_
#define LIBEMBED_HAL_UART_TYPES_H_

/**
 * @brief Hardware abstraction layer for the universal asynchronous receiver and transmitter (UART).
 */
namespace embed::uart {
    /**
     * @brief Opaque data structure representing a hardware UART interface.
     */
    typedef struct __UART_HardwareInterface UART_HardwareInterface;

    /**
     * @brief Type used for baudrate indication.
     */
    typedef uint32_t Baudrate;

    /**
     * @brief Type used for a single UART data frame.
     */
    typedef uint16_t DataFrame;

    /**
     * @brief UART stop bit mode enumerator.
     */
    typedef enum {
        //! 1 stop bit
        STOPBIT_1,
        //! 2 stop bits
        STOPBIT_2,
    } StopBitMode;
    
    /**
     * @brief UART Parity Mode Enumerator.
     */
    typedef enum {
        //! Parity disabled
        PARITY_DISABLED,
        //! Even parity
        PARITY_EVEN,
        //! Odd parity
        PARITY_ODD
    } ParityMode;

    /**
     * @brief Base class for UART interfaces.
     * 
     * Do not use this directly, use one of the implementations of this class instead.
     */
    class UART_Base {
        public:
            /**
             * @brief Initializes the @ref UART_Base class.
             */
            UART_Base();

            /**
             * @brief Initializes the UART interface with the specified parameters.
             * 
             * @param baudrate The baudrate to use for the interface.
             * @param wordLength The word length to use for the interface in bits.
             * @param parityMode The parity mode to use for the interface.
             * @param stopBitMode The stop bit mode to use for the interface.
             */
            virtual void begin(Baudrate baudrate = 9600, uint8_t wordLength = 8, ParityMode parityMode = PARITY_DISABLED, StopBitMode stopBitMode = STOPBIT_1) = 0;

            /**
             * @brief Writes a single frame with the specified data to the UART interface.
             * 
             * @param data Data to send to the interface.
             * @param timeout Timeout for sending the data.
             */
            virtual void writeFrame(DataFrame data, uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT) = 0;

            /**
             * @brief Receive a single from the UART interface.
             * 
             * @param timeout The maximum time to wait for before returning.
             * 
             * @return Returns the received data.
             */
            virtual DataFrame recvFrame(uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_RECV_TIMEOUT) = 0;

            /**
             * @brief Sends a string to the UART interface.
             * 
             * @param data The string to send to UART interface.
             */
            void write(std::string data);
    };

    /**
     * @brief Base class for hardware UART interfaces.
     * 
     * Do not use this directly, use one of the implementations of this class instead.
     */
    class HardwareUART_Base : public UART_Base {
        public:
            //! Hardware UART interface
            const UART_HardwareInterface& interface;

            /**
             * @brief Construct a new HardwareUART_Base object.
             * 
             * @param interface The interface you want to assign to the HardwareUART object.
             */
            HardwareUART_Base(uart::UART_HardwareInterface& interface);

            virtual void begin(Baudrate baudrate = 9600, uint8_t wordLength = 8, ParityMode parityMode = PARITY_DISABLED, StopBitMode stopBitMode = STOPBIT_1) = 0;
            virtual void writeFrame(DataFrame data, uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_SEND_TIMEOUT) = 0;
            virtual DataFrame recvFrame(uint32_t timeout = LIBEMBED_CONFIG_STM32_UART_DEFAULT_RECV_TIMEOUT) = 0;
    };
}

#endif /* LIBEMBED_HAL_UART_TYPES_H_ */