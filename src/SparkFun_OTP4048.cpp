#include "SparkFun_OPT4048.h"
#include "sfe_bus.h"

QwOpt4048::QwOpt4048()
{
}

/// @brief Sets the struct that interfaces with STMicroelectronic's C Library.
/// @return true on successful execution.
bool QwOpt4048::init(void)
{
    if (!_sfeBus->ping(_i2cAddress))
        return false;

    if (getUniqueId() != OPT4048_DEVICE_ID)
        return false;

    return true;
}

/// @brief Checks that the bus is connected with the OPT4048 by checking
/// it's unique ID.
/// @return True on successful execution.
bool QwOpt4048::isConnected()
{
    if (getUniqueId() != OPT4048_DEVICE_ID)
        return false;
    else
        return true;
}

/// @brief Retrieves the the device's ID: 0x2108 for the OPT4048.
/// @return Returns the unique ID.
uint16_t QwOpt4048::getUniqueId()
{

    uint8_t buff[2];
    uint16_t uniqueId;
    int32_t retVal;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_DEVICE_ID, buff);

    uniqueId = buff[0] << 8;
    uniqueId |= buff[1];

    if (retVal != 0)
        return 0;

    return uniqueId;
}

/// @brief Sets the pointer to the data bus for read and writes.
/// @param theBus This parameter sets the the I2C hardware bus.
/// @param i2cAddress The I2C address for the device.
void QwOpt4048::setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus, uint8_t i2cAddress)
{
    _sfeBus = &theBus;
    _i2cAddress = i2cAddress;
}

/// @brief Sets the pointer to the data bus for read and writes.
/// @param theBus This parameter sets the hardware bus.
void QwOpt4048::setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus)
{
    _sfeBus = &theBus;
}

/// @brief Writes to the data to the given register using the hardware data bus.
/// @param  offset The register to write to.
/// @param  data The data to write to the register.
/// @param  length The number of writes
/// @return The successful (0) or unsuccessful (-1) write to the given register.
int32_t QwOpt4048::writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->writeRegisterRegion(_i2cAddress, offset, data, length);
}

/// @brief Reads data from the specified register using the set data bas.
/// @param  offset The register to read from.
/// @param  data The pointer to the value to store the value.
/// @param  length The number of reads
/// @return The successful (0) or unsuccessful (-1) read of the given register.
int32_t QwOpt4048::readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->readRegisterRegion(_i2cAddress, offset, data, length);
}

bool QwOpt4048::setRange(opt4048_range_t range)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.range = range;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, &range);

    if (retVal != 0)
        return false;

    return true;
}