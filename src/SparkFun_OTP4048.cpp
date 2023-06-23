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

    uniqueId = buff[1] << 8;
    uniqueId |= buff[0];

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

/// @brief Sets the OPT4048's effective sensing range which will effect its resolution.
/// @param range The range to set the device to.
///   RANGE_2KLUX2,
///   RANGE_4KLUX5,
///   RANGE_9LUX,
///   RANGE_18LUX,
///   RANGE_36LUX,
///   RANGE_72LUX,
///   RANGE_144LUX,
///   RANGE_AUTO
/// @return True on successful execution.
bool QwOpt4048::setRange(opt4048_range_t range)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.range = range;

    buff[1] = controlReg >> 8;
    buff[0] = controlReg;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, &range);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Sets the OPT4048's conversion time which will effect its resolution. Longer conversion time
/// will result in higher resolution.
/// @param time The conversion time to set the device to. Possible values:
///   CONVERSION_TIME_600US,
///   CONVERSION_TIME_1MS,
///   CONVERSION_TIME_1MS8,
///   CONVERSION_TIME_3MS4,
///   CONVERSION_TIME_6MS5,
///   CONVERSION_TIME_12MS7,
///   CONVERSION_TIME_25MS,
///   CONVERSION_TIME_50MS,
///   CONVERSION_TIME_100MS,
///   CONVERSION_TIME_200MS,
///   CONVERSION_TIME_400MS,
///   CONVERSION_TIME_800MS
/// @return True on successful execution.
bool QwOpt4048::setConversionTime(opt4048_conversion_time_t time)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.conversionTime = time;

    buff[1] = controlReg >> 8;
    buff[0] = controlReg;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Enable the quick wake uup feature of the OPT4048.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOPT4048::enableQwake(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.qwakeEnable = (uint8_t)enable;

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Sets the OPT4048's operation mode.
/// @param mode The mode to set the device to. Possible Values:
///   OPERATION_MODE_POWER_DOWN,
///   OPERATION_MODE_AUTO_ONE_SHOT,
///   OPERATION_MODE_ONE_SHOT,
///   OPERATION_MODE_CONTINUOUS
/// @return
bool QwOPT4048::setOperationMode(opt4048_operation_mode_t mode)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.operationMode = mode;

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Changes the behavior of the interrupt from pin to latch.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOPT4048::enableIntLatch(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.latch = (uint8_t)enable;

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Sets the OPT4048's interrupt polarity.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOPT4048::enableIntActiveHigh(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[1] << 8;
    intReg.word |= buff[0];

    intReg.int_pol = (uint8_t)enable;

    buff[1] = intReg.word >> 8;
    buff[0] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Changes the behavior of the interrupt pin to be an INPUT to trigger
/// single shot. 
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOPT4048::enableIntInput(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[1] << 8;
    intReg.word |= buff[0];

    intReg.int_dir = (uint8_t)enable;

    buff[1] = intReg.word >> 8;
    buff[0] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Changes the behavior interrupt mechanism after the end of conversion
/// @param mechanism The mechanism to set
/// @return True on successful execution.
bool QwOPT4048::enableIntMechanism(opt4048_mechanism_t mechanism)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[1] << 8;
    intReg.word |= buff[0];

    intReg.int_cfg = mechanism;

    buff[1] = intReg.word >> 8;
    buff[0] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Sets the flag.
/// @param flag The flag to set
/// @return True on successful execution.
bool QwOPT4048::setFlag(opt4048_reg_control_t flag)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t flagReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_FLAGS, buff);

    if (retVal != 0)
        return false;

    flagReg.word = buff[1] << 8;
    flagReg.word |= buff[0];
    
    flagReg.word |= flag; 

    buff[1] = flagReg.word >> 8;
    buff[0] = flagReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_FLAGS, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Enables the overload flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableOverloadFlag(bool enable)
{
    opt4048_reg_control_t flagReg;

    flagReg.overload_flag = 1; 

    if(!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the conversion ready flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableOverloadFlag(bool enable)
{
    opt4048_reg_control_t flagReg;

    flagReg.conv_ready_flag = 1; 

    if(!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the flag high flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableTooBrightFlag(bool enable)
{
    opt4048_reg_control_t flagReg;

    flagReg.flag_high = 1; 

    if(!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the flag low flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableTooDimFlag(bool enable)
{
    opt4048_reg_control_t flagReg;

    flagReg.flag_low = 1; 

    if(!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Sets the number of faults (light values over or under) before an interrupt is triggered.
/// @param count The number of faults to trigger an interrupt
///   FAULT_COUNT_1,
///   FAULT_COUNT_2,
///   FAULT_COUNT_4,
///   FAULT_COUNT_8
/// @return True on successful execution. 
bool QwOPT4048::setFaultCount(opt4048_fault_count_t count)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.fault_count = count;

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Sets the channel for threshold logic 
/// @param channel The channel to set the threshold logic to. 
///   THRESH_CHANNEL_CH0,
///   THRESH_CHANNEL_CH1,
///   THRESH_CHANNEL_CH2,
///   THRESH_CHANNEL_CH3
/// @return True on successful execution. 
bool QwOPT4048::setThresholdChannel(opt4048_threshold_channel_t channel)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[1] << 8;
    intReg.word |= buff[0];

    intReg.threshold_ch_sel = channel;

    buff[1] = intReg.word >> 8;
    buff[0] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Enable register auto increment .
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableI2CBurst(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[1] << 8;
    intReg.word |= buff[0];

    intReg.i2c_burst = (uint8_t)enable;

    buff[1] = intReg.word >> 8;
    buff[0] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Enable CRC for ADC calues
/// @param enable True to enable, false to disable.
/// @return True on successful execution. 
bool QwOPT4048::enableCRC(bool enable)
{
    crcEnabled = true;  
}


