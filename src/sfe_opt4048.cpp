#include "sfe_opt4048.h"
#include "OPT4048_Registers.h"

/// @brief Sets the struct that interfaces with STMicroelectronic's C Library.
/// @return true on successful execution.
bool QwOpt4048::init(void)
{
    if (!_sfeBus->ping(_i2cAddress))
        return false;

    if (getDeviceID() != OPT4048_DEVICE_ID)
        return false;

    return true;
}

/// @brief Checks that the bus is connected with the OPT4048 by checking
/// it's unique ID.
/// @return True on successful execution.
bool QwOpt4048::isConnected()
{
    if (getDeviceID() != OPT4048_DEVICE_ID)
        return false;
    else
        return true;
}

/// @brief Retrieves the the device's ID: 0x24 for the OPT4048.
/// @return Returns the unique ID.
uint16_t QwOpt4048::getDeviceID()
{

    uint8_t buff[2];
    uint16_t uniqueId;
    int32_t retVal;
    opt4048_reg_device_id_t idReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_DEVICE_ID, buff);

    idReg.word = buff[0] << 8;
    idReg.word |= buff[1];

    uniqueId = idReg.DIDH2 << 10; 
    uniqueId |= idReg.DIDH << 2; 
    uniqueId |= idReg.DIDL;  
    Serial.print("Device ID: ");
    Serial.println(uniqueId, HEX);

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

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.range = range;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Retrieves the light range in lux of the OPT4048. 
/// @return The range of lux able to be measured. 
opt4048_range_t QwOpt4048::getRange()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    
    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_range_t)controlReg.range;
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

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.conversion_time = time;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Retrieves the conversion time used for the ADC. 
/// @return The OPT4048 conversion time. 
opt4048_conversion_time_t QwOpt4048::getConversionTime()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_conversion_time_t)controlReg.conversion_time;
}

/// @brief Enable the quick wake up feature of the OPT4048.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableQwake(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.qwake = (uint8_t)enable;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Checks the quick wake bit. 
/// @return True the quick wake bit is set. 
bool QwOpt4048::getQwake()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    if( controlReg.qwake != 0x01)
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
bool QwOpt4048::setOperationMode(opt4048_operation_mode_t mode)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.op_mode = mode;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Retrieves the set operation mode.
/// @return The OPT4048 conversion time. 
opt4048_operation_mode_t QwOpt4048::getOperationMode()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_operation_mode_t)controlReg.op_mode;
}

/// @brief Changes the behavior of the interrupt from pin to latch.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableIntLatch(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.latch = (uint8_t)enable;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Checks if the interrupt is set to pulse or latch. 
/// @return True if set to latch, false if not. 
bool QwOpt4048::getIntLatch()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    if(controlReg.latch == 1)
        return true;

    return false; 
}

/// @brief Sets the OPT4048's interrupt polarity.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableIntActiveHigh(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.int_pol = (uint8_t)enable;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Sets the OPT4048's interrupt polarity.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::getIntActiveHigh()
{
    uint8_t buff[2];
    opt4048_reg_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    if(!intReg.int_pol)
        return false; 

    return true;   
}

/// @brief Changes the behavior of the interrupt pin to be an INPUT to trigger
/// single shot.
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableIntInput(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.int_dir = (uint8_t)enable;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Gets the interrupt input bit
/// @return True if the interrupt is set to INPUT. 
bool QwOpt4048::getIntInputEnable()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    Serial.println("Interrupt Enable Register: ");
    Serial.print("Expecting: Registers One - Register Two: ");
    Serial.println("10000000 - 00010001");
    Serial.print("Actual: ");
    Serial.print(buff[0], BIN);
    Serial.print("-");
    Serial.println(buff[1], BIN);
    Serial.print("What's stored in the word: ");
    Serial.println(intReg.word, BIN);
    Serial.print("i2c Burst: ");
    Serial.println(intReg.i2c_burst, BIN);
    Serial.print("Reserved Two: ");
    Serial.println(intReg.reserved_two, BIN);
    Serial.print("int_cfg: ");
    Serial.println(intReg.int_cfg, BIN);
    Serial.print("i2c Direction: ");
    Serial.println(intReg.int_dir, BIN);
    Serial.print("Threshold_ch_sel: ");
    Serial.println(intReg.int_dir, BIN);
    Serial.print("Reserved One: ");
    Serial.println(intReg.reserved_one, BIN);
    if(!intReg.int_dir)
        return false; 

    return true; 
}


/// @brief Changes the behavior interrupt mechanism after the end of conversion
/// @param mechanism The mechanism to set
/// @return True on successful execution.
bool QwOpt4048::setIntMechanism(opt4048_mechanism_t mechanism)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.int_cfg = mechanism;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Gets the interrupt mechanism for the OPT4048
/// @return Returns the enabled mechanism.
opt4048_mechanism_t QwOpt4048::getIntMechanism()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    return((opt4048_mechanism_t)intReg.int_cfg);

}

/// @brief Retrieves the flag register
/// @return The contents of the flag register
opt4048_reg_flags_t QwOpt4048::getAllFlags()
{
    uint8_t buff[2];
    opt4048_reg_flags_t flagReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_FLAGS, buff);

    flagReg.word = buff[0] << 8;
    flagReg.word |= buff[1];

    return flagReg;
}

/// @brief Checks the overload flag bit. 
/// @return True if the overload flag bit is set, false otherwise
bool QwOpt4048::getOverloadFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if(flagReg.overload_flag != 1)
        return false;

    return true;
}



/// @brief Checks the conversion ready flag bit. 
/// @return True if that flag bit is set, false otherwise
bool QwOpt4048::getConvReadyFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if(flagReg.conv_ready_flag != 1)
        return false;

    return true;
}

/// @brief Checks the too bright flag bit. 
/// @return True if that flag bit is set, false otherwise
bool QwOpt4048::getTooBrightFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if(flagReg.flag_high != 1)
        return false;

    return true;
}

/// @brief Checks the too dim flag bit. 
/// @return True if that flag bit is set, false otherwise
bool QwOpt4048::getTooDimFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if(flagReg.flag_low != 1)
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
bool QwOpt4048::setFaultCount(opt4048_fault_count_t count)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    controlReg.fault_count = count;

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Retrieves the number of faults (light values over or under) before an interrupt is triggered.
/// @return The fault count. 
opt4048_fault_count_t QwOpt4048::getFaultCount()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;
    controlReg.fault_count = 0; 

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return((opt4048_fault_count_t)controlReg.fault_count);

}

/// @brief Sets the channel for threshold logic
/// @param channel The channel to set the threshold logic to.
///   THRESH_CHANNEL_CH0,
///   THRESH_CHANNEL_CH1,
///   THRESH_CHANNEL_CH2,
///   THRESH_CHANNEL_CH3
/// @return True on successful execution.
bool QwOpt4048::setThresholdChannel(opt4048_threshold_channel_t channel)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.threshold_ch_sel = channel;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Retrives the threshold channel.
/// @return True on successful execution.
opt4048_threshold_channel_t QwOpt4048::getThresholdChannel()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    return((opt4048_threshold_channel_t)intReg.threshold_ch_sel);
}

/// @brief Sets the Lux High Value threshold. 
/// @param thresh The value in float
/// @return Returns the high threshold. 
bool QwOpt4048::setThresholdHigh(float thresh)
{
    if(thresh < 2.15 || thresh > 144000)
        return false; 

    uint8_t buff[2];
    int32_t retVal;
    //opt4048_reg_thresh_exp_res_high_t threshReg; 

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_THRESH_H_EXP_RES, buff);

    if(retVal != 0)
        return false;

    return true;
    
}

/// @brief Retrieves the Lux High Value threshold. 
/// @return Returns the high threshold. 
uint16_t QwOpt4048::getThresholdHigh()
{
    uint8_t buff[2];
    opt4048_reg_thresh_exp_res_high_t threshReg; 
    uint16_t thresholdHigh; 

    readRegisterRegion(SFE_OPT4048_REGISTER_THRESH_H_EXP_RES, buff);

    threshReg.word = buff[0] << 8;
    threshReg.word |= buff[1];

    thresholdHigh = threshReg.thresh_result << threshReg.thresh_exp; 

    return thresholdHigh; 
}

/// @brief Sets the Lux Low Value threshold. 
/// @param thresh The value in float
/// @return Returns the high threshold. 
bool QwOpt4048::setThresholdLow(float thresh)
{
    if(thresh < 2.15 || thresh > 144000)
        return false; 

    uint8_t buff[2];
    int32_t retVal;
    //opt4048_reg_thresh_exp_res_low_t threshReg; 

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_THRESH_L_EXP_RES, buff);

    if(retVal != 0)
        return false;

    return true;
    
}



/// @brief Retrieves the Lux Low Value threshold. 
/// @return Returns the low threshold. 
uint16_t QwOpt4048::getThresholdLow()
{
    uint8_t buff[2];
    opt4048_reg_thresh_exp_res_low_t threshReg; 
    uint16_t thresholdLow; 

    readRegisterRegion(SFE_OPT4048_REGISTER_THRESH_L_EXP_RES, buff);

    threshReg.word = buff[0] << 8;
    threshReg.word |= buff[1];

    thresholdLow = threshReg.thresh_result << threshReg.thresh_exp; 

    return thresholdLow; 
}

/// @brief Enable register auto increment .
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableI2CBurst(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.i2c_burst = (uint8_t)enable;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}


/// @brief Retrieves the I2C burst bit. 
/// @return True if I2C burst is enabled, false otherwise. 
bool QwOpt4048::getI2CBurst()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    if(intReg.i2c_burst != 1)
        return false;

    return true;
}

/// @brief Enable CRC for ADC calues
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
void QwOpt4048::enableCRC(bool enable)
{
    crcEnabled = true;
}

/// @brief Reads Channel Zero (Red)
/// @return Returns the ADC value of Channel Zero
uint32_t QwOpt4048::getADCCh0()
{
    uint8_t buff[4];
    uint8_t expon;
    uint32_t adcCode;
    uint32_t mantissa;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH0, buff, 4);


    expon = (buff[0] >> 8) & 0xF0; // Four bit expon
    mantissa = buff[1] << 16;      // Four bits of mantissa
    mantissa |= buff[0] << 8;      // 8 more bits of mantissa
    mantissa |= buff[3];           // 8 more bits of mantissa - 20 total.

    adcCode = mantissa << expon;

    return adcCode;
}

/// @brief Reads Channel One (Green)
/// @return Returns the ADC value of Channel One
uint32_t QwOpt4048::getADCCh1()
{

    uint8_t buff[4];
    uint32_t adcCode;
    uint32_t mantissa;
    opt4048_reg_exp_res_ch1_t adcReg; 
    opt4048_reg_res_cnt_crc_ch1_t adc1Reg; 

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH1, buff, 4);

    adcReg.word = buff[0] << 8; 
    adcReg.word |= buff[1]; 
    adc1Reg.word = buff[2] << 8; 
    adc1Reg.word |= buff[3]; 

    mantissa = adcReg.result_msb_ch1 << 8; 
    mantissa |= adc1Reg.result_lsb_ch1; 

    adcCode = mantissa << adcReg.exponent_ch1; 
    Serial.print("Exponent (should be ): ");
    Serial.println(adcReg.exponent_ch1, HEX);

    return adcCode;
}

/// @brief Reads Channel Two (Blue)
/// @return Returns the ADC value of Channel Two
uint32_t QwOpt4048::getADCCh2()
{

    uint8_t buff[4];
    uint8_t expon;
    uint32_t adcCode;
    uint32_t mantissa;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH2, buff, 4);

    expon = (buff[0] >> 8) & 0xF0; // Four bit expon
    mantissa = buff[1] << 16;      // Four bits of mantissa
    mantissa |= buff[0] << 8;      // 8 more bits of mantissa
    mantissa |= buff[3];           // 8 more bits of mantissa - 20 total.

    adcCode = mantissa << expon;

    return adcCode;
}

/// @brief Reads Channel Three (White)
/// @return Returns the ADC value of Channel Three
uint32_t QwOpt4048::getADCCh3()
{

    uint8_t buff[4];
    uint8_t expon;
    uint32_t adcCode;
    uint32_t mantissa;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH3, buff, 4);

    expon = (buff[0] >> 8) & 0xF0; // Four bit expon
    mantissa = buff[1] << 16;      // Four bits of mantissa
    mantissa |= buff[0] << 8;      // 8 more bits of mantissa
    mantissa |= buff[3];           // 8 more bits of mantissa - 20 total.

    adcCode = mantissa << expon;

    return adcCode;
}

/// @brief Retrieves all ADC values for all channels: Red, Green, Blue, and White.
/// @return Returns the ADC values of the channels.
sfe_color_t QwOpt4048::getAllADC()
{

    sfe_color_t color;

    color.red = getADCCh0();
    color.green = getADCCh1();
    color.blue = getADCCh2();
    color.white = getADCCh3();

    return color;
}

/// @brief Retrieves all ADC values for all channels: Red, Green, Blue, and White, as well as the sample counter, and
///        the CRC value.
/// @param color Pointer to the color struct to be populated with the channels values.
/// @return Returns true on successful execution, false otherwise.
bool QwOpt4048::getAllChannelData(sfe_color_t *color)
{
    uint8_t expon;
    uint8_t crc;
    int32_t retVal;
    uint32_t mantissa;

    // Iterators
    uint8_t chan;
    uint8_t offset;
    uint8_t buff[16]= {0};
    uint8_t crcArr[4]= {0};
    uint8_t counterArr[4]= {0};
    uint32_t adcArr[4]= {0};

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH0, buff, 16);

    if (retVal != 0)
        return false;

    for (chan = 0, offset = 0; offset < 4; chan++, offset += 4)
    {
        expon = (buff[0 + offset] >> 8) & 0xF0; // Four bit expon
        mantissa = buff[1 + offset] << 16;      // Four bits of mantissa
        mantissa |= buff[0 + offset] << 8;      // 8 more bits of mantissa
        mantissa |= buff[3 + offset];           // 8 more bits of mantissa - 20 total.
        crc = buff[2 + offset] & 0x0F;
        counterArr[chan] = buff[2] >> 4;
        adcArr[chan] = mantissa << expon;

        if (crcEnabled == true)
        {
            crcArr[chan] = calculateCRC(mantissa, expon, crc);
        }

        chan++;
    }

    color->red = adcArr[0];
    color->green = adcArr[1];
    color->blue = adcArr[2];
    color->white = adcArr[3];

    color->counterR = counterArr[0];
    color->counterG = counterArr[1];
    color->counterR = counterArr[2];
    color->counterR = counterArr[3];

    color->CRCR = crcArr[0];
    color->CRCG = crcArr[1];
    color->CRCB = crcArr[2];
    color->CRCW = crcArr[3];

    return true;
}

/// @brief  Calculates the CRC for the OPT4048. Note that the OPT4048 does this already
///         but this is a way to double check the value.
/// @param mantissa The mantissa value of the ADC
/// @param exponent The exponent value of the ADC
/// @param crc The CRC value of the ADC
/// @return Returns the calculated CRC value.
uint8_t QwOpt4048::calculateCRC(uint32_t mantissa, uint8_t expon, uint8_t crc)
{

    mantissaBits mBits;
    exponBits exBits;
    crcBits cBits;
    crcBits compareAgainst;

    mBits.word = mantissa;
    exBits.byte = expon;
    cBits.byte = crc;

    compareAgainst.bit0 = exBits.byte xor mantissa xor cBits.byte;

    compareAgainst.bit1 =
        cBits.bit1 xor cBits.bit3 xor mBits.bit1 xor mBits.bit3 xor
        mBits.bit5 xor mBits.bit7 xor mBits.bit9 xor
        mBits.bit11 xor mBits.bit13 xor mBits.bit15 xor mBits.bit17 xor
        mBits.bit19 xor exBits.bit1 xor exBits.bit3;

    compareAgainst.bit2 =
        cBits.bit3 xor mBits.bit3 xor mBits.bit7 xor mBits.bit11 xor
        mBits.bit16 xor mBits.bit18 xor exBits.bit3;

    compareAgainst.bit3 = mBits.bit3 xor mBits.bit11 xor mBits.bit19;

    if (compareAgainst.byte == crc)
        return 1;

    return 0;
}

/// @brief Retrieves the Lux value.
/// @return Returns the Lux value of the sensor
uint32_t QwOpt4048::getLux()
{
    uint32_t adcCh1;
    uint32_t lux;

    adcCh1 = getADCCh1();
    lux = adcCh1 * cieMatrix[1][3];

    return lux;
}

/// @brief  Retrieves the CIE X value of the sensor.
/// @return Returns the CIE X value of the sensor
uint32_t QwOpt4048::getCIEx()
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint32_t CIEx;
    sfe_color_t color;

    getAllChannelData(&color);

    for (int col = 0; col < OPT_MATRIX_COLS; col++)
    {
        x += color.red * cieMatrix[0][col];
        y += color.green * cieMatrix[1][col];
        z += color.blue * cieMatrix[2][col];
    }

    CIEx = x / (x + y + z);

    return CIEx;
}

/// @brief Retrieves the CIE Y value of the sensor.
/// @return Returns the CIE Y value of the sensor
uint32_t QwOpt4048::getCIEy()
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint32_t CIEy;
    sfe_color_t color;

    getAllChannelData(&color);

    for (int col = 0; col < OPT_MATRIX_COLS; col++)
    {
        x += color.red * cieMatrix[0][col];
        y += color.green * cieMatrix[1][col];
        z += color.blue * cieMatrix[2][col];
    }

    CIEy = y / (x + y + z);

    return CIEy;
}

/// @brief Retrieves the Correlated Color Temperature (CCT) of the sensor.
/// @return Returns the CCT of the sensor in Kelvin
uint32_t QwOpt4048::getCCT()
{
    uint32_t CIEx;
    uint32_t CIEy;
    uint32_t CCT;

    CIEx = getCIEx();
    CIEy = getCIEy();

    CCT = (CIEx - 0.3320) / (0.1858 - CIEy);

    return CCT;
}
