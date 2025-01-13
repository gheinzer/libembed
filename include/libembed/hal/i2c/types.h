/**
 * @file types.h
 * @author Gabriel Heinzer
 * @brief Common type definitions for @ref libembed/hal/i2c.h.
 */

#include <stdint.h>
#include <string>
#include <libembed/config.h>

#ifndef LIBEMBED_HAL_I2C_TYPES_H_
#define LIBEMBED_HAL_I2C_TYPES_H_

/**
 * @brief Hardware abstraction layer for the inter-integrated circuit interface (I2C).
 */
namespace embed::i2c {
    /**
     * @brief Opaque data structure representing a hardware I2C interface.
     */
    typedef struct __I2C_HardwareInterface I2C_HardwareInterface;

    //! Type used for I2C clock frequencies
    typedef uint32_t ClockFrequency;

    //! Type used for 7-Bit I2C addresses
    typedef uint8_t Address_7B;

    /**
     * @brief Enumerator used for the indication of the 
     * I2C communication direction.
     */
    typedef enum {
        //! Read direction, i.e. from slave to master
        READ = 1,
        //! Write direction, i.e. from master to slave
        WRITE = 0
    } Direction;

    /**
     * @brief Enumerator defining the I2C acknowlegement types. 
     */
    typedef enum {
        //! I2C acknowledgement (ACK)
        ACK,
        //! I2C negative acknoledgement (NACK)
        NACK
    } AcknowledgementType;

    /**
     * @brief Base class for master I2C interfaces.
     * 
     * Do not use this directly, use one of the implementations of this class instead.
     */
    class I2C_Master_Base {
        public:
            /**
             * @brief Initializes the @ref I2C_Master_Base class.
             */
            I2C_Master_Base();

            /**
             * @brief Initializes the I2C interface with the specified parameters.
             * 
             * @param freq The frequency you want to use for the interface.
             */
            virtual void begin(ClockFrequency freq) = 0;

            /**
             * @brief Starts a message, i.e. sends a start condition
             * with the following adress and direction bit.
             * 
             * This can also be used to send a repeated start condition.
             * 
             * @note This implements limited coroutine safety: Calls to @ref startMessage are queued
             * and executed sequentially. However, this does not prevent you from mixing multiple
             * messages.
             * 
             * @param address Slave address to send.
             * @param direction Direction bit value to send.
             * 
             * @return Returns the type of acknowledgement received after the address byte.
             */
            virtual AcknowledgementType startMessage(Address_7B address, Direction direction) = 0;

            /**
             * @brief Stops the mesage, i.e. sends stop condition.
             * 
             * @note This implements limited coroutine safety: Calls to @ref stopMessage are queued
             * and executed sequentially. However, this does not prevent you from mixing multiple
             * messages.
             */
            virtual void stopMessage() = 0;

            /**
             * @brief Sends a byte to the interface and awaits an
             * acknowlegement.
             * 
             * @note This implements limited coroutine safety: Calls to @ref sendByte are queued
             * and executed sequentially. However, this does not prevent you from mixing multiple
             * messages.
             * 
             * @param data The data to send.
             * @return The acknowledgement which was returned from the slave device.
             */
            virtual AcknowledgementType sendByte(uint8_t data) = 0;

            /**
             * @brief Reads a byte from the interface and returns the
             * specified acknowledgement.
             * 
             * @note This implements limited coroutine safety: Calls to @ref readByte are queued
             * and executed sequentially. However, this does not prevent you from mixing multiple
             * messages.
             * 
             * @param ackType Whether to return a `ACK` or `NACK` upon receiving the data.
             * @return The received data.
             */
            virtual uint8_t readByte(AcknowledgementType ackType = ACK) = 0;
    };

    /**
     * @brief Base class for hardware I2C interfaces.
     * 
     * Do not use this directly, use one of the implementation of this class instead.
     */
    class HardwareI2C_Master_Base : public I2C_Master_Base {
        public:
            //! Hardware I2C interface
            const I2C_HardwareInterface& interface;

            /**
             * @brief Construct a new @ref HardwareI2C_Master_Base object.
             * 
             * @param interface The interface to assign to this object.
             */
            HardwareI2C_Master_Base(I2C_HardwareInterface& interface);

            using I2C_Master_Base::begin;
            using I2C_Master_Base::readByte;
            using I2C_Master_Base::sendByte;
            using I2C_Master_Base::startMessage;
            using I2C_Master_Base::stopMessage;
    };
}

#endif /* LIBEMBED_HAL_I2C_TYPES_H_ */