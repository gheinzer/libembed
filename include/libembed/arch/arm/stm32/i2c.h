/**
 * @file i2c.h
 * @author Gabriel Heinzer
 * @brief I2C HAL specific to STM32.
 */

#include <libembed/hal/i2c/types.h>
#include <libembed/arch/ident.h>
#include "stm32_hal.h"

#ifndef LIBEMBED_ARCH_ARM_STM32_I2C_H_
#define LIBEMBED_ARCH_ARM_STM32_I2C_H_

#include LIBEMBED_STRINGIFY(LIBEMBED_MCU_LINE/i2c.h)

//! STM32-specific UART implementation
namespace embed::arch::arm::stm32::i2c {
    using namespace embed::i2c;
    using namespace embed::arch::arm::stm32::LIBEMBED_MCU_LINE::i2c;

    /**
     * @brief STM32 implementation of a hardware UART interface.
     */
    class HardwareI2C_Master : public HardwareI2C_Master_Base {
        public:
            using HardwareI2C_Master_Base::HardwareI2C_Master_Base;

            void begin(ClockFrequency freq) override;
            void startMessage(Address_7B address, Direction direction) override;
            void stopMessage() override;
            AcknowledgementType sendByte(uint8_t data) override;
            uint8_t readByte(AcknowledgementType ackType = ACK) override;
    };
}

#endif /* LIBEMBED_ARCH_ARM_STM32_I2C_H_ */