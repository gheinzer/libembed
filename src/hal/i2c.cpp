#include <libembed/hal/i2c.h>

using namespace embed;

i2c::I2C_Master_Base::I2C_Master_Base() { }
i2c::HardwareI2C_Master_Base::HardwareI2C_Master_Base(i2c::I2C_HardwareInterface& interface) : interface(interface) { }