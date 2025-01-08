#include <libembed/hal/i2c/types.h>
#include <libembed/util/coroutines.h>
#include <libembed/arch/arch.h>
#include <libembed/arch/arm/stm32/stm32_hal.h>
#include <libembed/arch/ident.h>
#include <libembed/arch/arm/stm32/i2c.h>
#include "../i2c_types.h"

#if STM32F412xx

using namespace embed::arch::stm32;

i2c::I2C_HardwareInterface i2c::I2C_1 = { .interface = I2C1 };
i2c::I2C_HardwareInterface i2c::I2C_2 = { .interface = I2C2 };
i2c::I2C_HardwareInterface i2c::I2C_3 = { .interface = I2C3 };

static embed::coroutines::Lock i2cLock;

static void i2c_enable_clocks_() {
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();
    __HAL_RCC_I2C3_CLK_ENABLE();
}

void i2c::HardwareI2C_Master::begin(i2c::ClockFrequency freq) {
    i2c_enable_clocks_();

    double fpclk1 = HAL_RCC_GetPCLK1Freq();
    double ttarget = 1.0 / freq;
    double tpclk1 = 1.0 / fpclk1;
    double triseValue = (0.000001 / tpclk1) + 1.0;
    double CCRval = ttarget / tpclk1;

    // Set the clock rate and the IF to standard speed mode
    interface.interface->CCR = CCRval;
    interface.interface->TRISE = triseValue;

    // Configure the clock frequency the interface requires
    interface.interface->CR2 = HAL_RCC_GetPCLK1Freq() / 1000000;

    // Enable the I2C peripheral
    SET_BIT(interface.interface->CR1, I2C_CR1_PE);
};

void i2c::HardwareI2C_Master::startMessage(i2c::Address_7B address, i2c::Direction direction) {
    i2cLock.acquire();

    // Send a start condition
    SET_BIT(interface.interface->CR1, I2C_CR1_START);

    // Wait for the start condition to be sent
    while(!READ_BIT(interface.interface->SR1, I2C_SR1_SB)) { yield; }

    // Clear the SB flag
    volatile uint32_t dummy = interface.interface->SR1;
    
    // Send the slave address and the RW bit
    interface.interface->DR = address << 1 | direction;

    // Wait for the slave address and R/W to be sent
    while(!READ_BIT(interface.interface->SR1, I2C_SR1_ADDR)) { yield; }
    
    // Clear the ADDR bit
    dummy = interface.interface->SR1 | interface.interface->SR2;
    while(READ_BIT(interface.interface->SR1, I2C_SR1_ADDR)) { yield; }

    i2cLock.release();
};

void i2c::HardwareI2C_Master::stopMessage() {
    i2cLock.acquire();

    SET_BIT(interface.interface->CR1, I2C_CR1_STOP);

    // Wait for the BUSY bit to be set to 0
    while(READ_BIT(interface.interface->SR1, I2C_SR2_BUSY)) { yield; }

    i2cLock.release();
};

i2c::AcknowledgementType i2c::HardwareI2C_Master::sendByte(uint8_t data) {
    i2cLock.acquire();

    // Wait for the transmitter to be ready
    while(!READ_BIT(interface.interface->SR1, I2C_SR1_TXE)) { yield; }

    // Transmit the byte
    interface.interface->DR = data;

    // Wait for the byte to be transmitted
    while(!READ_BIT(interface.interface->SR1, I2C_SR1_TXE)) { yield; }

    AcknowledgementType returnVal = (AcknowledgementType)(READ_BIT(interface.interface->SR1, I2C_SR1_BTF) > 1);

    i2cLock.release();

    return returnVal;
};

uint8_t i2c::HardwareI2C_Master::readByte(i2c::AcknowledgementType ackType) {
    while(!READ_BIT(interface.interface->SR1, I2C_SR1_RXNE)) { yield; };
    return interface.interface->DR;
};

#endif