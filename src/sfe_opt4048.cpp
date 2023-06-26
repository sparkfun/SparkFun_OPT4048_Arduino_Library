#include "sfe_opt4048.h"

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

/// @brief Retrieves the the device's ID: 0x2108 for the OPT4048.
/// @return Returns the unique ID.
uint16_t QwOpt4048::getDeviceID()
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

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

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

    controlReg.conversion_time = time;

    buff[1] = controlReg.word >> 8;
    buff[0] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

/// @brief Enable the quick wake uup feature of the OPT4048.
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

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.qwake = (uint8_t)enable;

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
bool QwOpt4048::setOperationMode(opt4048_operation_mode_t mode)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t controlReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    controlReg.word = buff[1] << 8;
    controlReg.word |= buff[0];

    controlReg.op_mode = mode;

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
bool QwOpt4048::enableIntLatch(bool enable)
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
bool QwOpt4048::enableIntActiveHigh(bool enable)
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
bool QwOpt4048::enableIntInput(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

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
bool QwOpt4048::setIntMechanism(opt4048_mechanism_t mechanism)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_int_control_t intReg;

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
bool QwOpt4048::setFlag(opt4048_reg_flags_t flag)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_flags_t flagReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_FLAGS, buff);

    if (retVal != 0)
        return false;

    flagReg.word = buff[1] << 8;
    flagReg.word |= buff[0];

    flagReg.word |= flag.word;

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
bool QwOpt4048::enableOverloadFlag(bool enable)
{
    opt4048_reg_flags_t flagReg;

    flagReg.overload_flag = 1;

    if (!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the conversion ready flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableConvReadyFlag(bool enable)
{
    opt4048_reg_flags_t flagReg;

    flagReg.conv_ready_flag = 1;

    if (!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the flag high flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableTooBrightFlag(bool enable)
{
    opt4048_reg_flags_t flagReg;

    flagReg.flag_high = 1;

    if (!setFlag(flagReg))
        return false;

    return true;
}

/// @brief Enables the flag low flag
/// @param enable True to enable, false to disable.
/// @return True on successful execution.
bool QwOpt4048::enableTooDimFlag(bool enable)
{
    opt4048_reg_flags_t flagReg;

    flagReg.flag_low = 1;

    if (!setFlag(flagReg))
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
bool QwOpt4048::setThresholdChannel(opt4048_threshold_channel_t channel)
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
bool QwOpt4048::enableI2CBurst(bool enable)
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
    uint8_t expon;
    uint32_t adcCode;
    uint32_t mantissa;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH1, buff, 4);

    expon = buff[0] >> 8 & 0xF0; // Four bit expon
    mantissa = buff[1] << 16;    // Four bits of mantissa
    mantissa |= buff[0] << 8;    // 8 more bits of mantissa
    mantissa |= buff[3];         // 8 more bits of mantissa - 20 total.

    adcCode = mantissa << expon;

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
sfe_color_t QwOpt4048::getAllChannels()
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
        cBits.bit1 xor cBits.bit3 xor mBits.bit1 xor mBits.bit3 xor mBits.bit5 xor mBits.bit7 xor mBits.bit9 xor
        mBits.bit11 xor mBits.bit13 xor mBits.bit15 xor mBits.bit17 xor mBits.bit19 xor exBits.bit1 xor exBits.bit3;

    compareAgainst.bit2 =
        cBits.bit3 xor mBits.bit3 xor mBits.bit7 xor mBits.bit11 xor mBits.bit16 xor mBits.bit18 xor exBits.bit3;

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
    lux = adcCh1 * cieMatrix[2][4];

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
