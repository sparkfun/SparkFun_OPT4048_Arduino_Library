/*
sfe_opt4048.cpp

SparkFun Tristimulus Color Sensor - OPT4048

Qwiic 1x1
* https://www.sparkfun.com/products/
Qwiic Mini
* https://www.sparkfun.com/products/

Repository:
* https://github.com/sparkfun/SparkFun_OPT4048_Arduino_Library

The MIT License (MIT)

Copyright (c) 2022 SparkFun Electronics
Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions: The
above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
"AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

License(http://opensource.org/licenses/MIT).

The following functions are for the QwOpt4048 class which handles the
main functionality for the OPT4048 IC.

*/
#include "sfe_opt4048.h"
#include "OPT4048_Registers.h"
#include <math.h>

bool QwOpt4048::init(void)
{
    if (!_sfeBus->ping(_i2cAddress))
        return false;

    if (getDeviceID() != OPT4048_DEVICE_ID)
        return false;

    return true;
}

bool QwOpt4048::isConnected()
{
    if (getDeviceID() != OPT4048_DEVICE_ID)
        return false;
    else
        return true;
}

uint16_t QwOpt4048::getDeviceID()
{

    uint8_t buff[2];
    uint16_t uniqueId;
    int32_t retVal;
    opt4048_reg_device_id_t idReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_DEVICE_ID, buff);

    idReg.word = buff[0] << 8;
    idReg.word |= buff[1];
    uniqueId = idReg.DIDH << 2;
    uniqueId |= idReg.DIDL;

    if (retVal != 0)
        return 0;

    return uniqueId;
}

void QwOpt4048::setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus, uint8_t i2cAddress)
{
    _sfeBus = &theBus;
    _i2cAddress = i2cAddress;
}

void QwOpt4048::setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus)
{
    _sfeBus = &theBus;
}

int32_t QwOpt4048::writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->writeRegisterRegion(_i2cAddress, offset, data, length);
}

int32_t QwOpt4048::readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->readRegisterRegion(_i2cAddress, offset, data, length);
}

void QwOpt4048::setBasicSetup()
{
    setRange(RANGE_36LUX);
    setConversionTime(CONVERSION_TIME_200MS);
    setOperationMode(OPERATION_MODE_CONTINUOUS);
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

    buff[0] = controlReg.word >> 8;
    buff[1] = controlReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

opt4048_range_t QwOpt4048::getRange()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_range_t)controlReg.range;
}

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

opt4048_conversion_time_t QwOpt4048::getConversionTime()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_conversion_time_t)controlReg.conversion_time;
}

bool QwOpt4048::setQwake(bool enable)
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

bool QwOpt4048::getQwake()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    if (controlReg.qwake != 0x01)
        return false;

    return true;
}

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

opt4048_operation_mode_t QwOpt4048::getOperationMode()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return (opt4048_operation_mode_t)controlReg.op_mode;
}

bool QwOpt4048::setIntLatch(bool enable)
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

bool QwOpt4048::getIntLatch()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    if (controlReg.latch == 1)
        return true;

    return false;
}

bool QwOpt4048::setIntActiveHigh(bool enable)
{
    uint8_t buff[2];
    int32_t retVal;
    opt4048_reg_control_t intReg;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    intReg.int_pol = (uint8_t)enable;

    buff[0] = intReg.word >> 8;
    buff[1] = intReg.word;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    if (retVal != 0)
        return false;

    return true;
}

bool QwOpt4048::getIntActiveHigh()
{
    uint8_t buff[2];
    opt4048_reg_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    if (!intReg.int_pol)
        return false;

    return true;
}

bool QwOpt4048::setIntInput(bool enable)
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

bool QwOpt4048::getIntInputEnable()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    if (!intReg.int_dir)
        return false;

    return true;
}

bool QwOpt4048::setIntMechanism(opt4048_int_cfg_t mechanism)
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

opt4048_int_cfg_t QwOpt4048::getIntMechanism()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    return ((opt4048_int_cfg_t)intReg.int_cfg);
}

opt4048_reg_flags_t QwOpt4048::getAllFlags()
{
    uint8_t buff[2];
    opt4048_reg_flags_t flagReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_FLAGS, buff);

    flagReg.word = buff[0] << 8;
    flagReg.word |= buff[1];

    return flagReg;
}

bool QwOpt4048::getOverloadFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if (flagReg.overload_flag != 1)
        return false;

    return true;
}

bool QwOpt4048::getConvReadyFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if (flagReg.conv_ready_flag != 1)
        return false;

    return true;
}

bool QwOpt4048::getTooBrightFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if (flagReg.flag_high != 1)
        return false;

    return true;
}

bool QwOpt4048::getTooDimFlag()
{
    opt4048_reg_flags_t flagReg;
    flagReg = getAllFlags();

    if (flagReg.flag_low != 1)
        return false;

    return true;
}

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

opt4048_fault_count_t QwOpt4048::getFaultCount()
{
    uint8_t buff[2];
    opt4048_reg_control_t controlReg;
    controlReg.fault_count = 0;

    readRegisterRegion(SFE_OPT4048_REGISTER_CONTROL, buff);

    controlReg.word = buff[0] << 8;
    controlReg.word |= buff[1];

    return ((opt4048_fault_count_t)controlReg.fault_count);
}

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

opt4048_threshold_channel_t QwOpt4048::getThresholdChannel()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    return ((opt4048_threshold_channel_t)intReg.threshold_ch_sel);
}

bool QwOpt4048::setThresholdHigh(float thresh)
{
    if (thresh < 2.15 || thresh > 144000)
        return false;

    uint8_t buff[2];
    int32_t retVal;
    // opt4048_reg_thresh_exp_res_high_t threshReg;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_THRESH_H_EXP_RES, buff);

    if (retVal != 0)
        return false;

    return true;
}

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

bool QwOpt4048::setThresholdLow(float thresh)
{
    if (thresh < 2.15 || thresh > 144000)
        return false;

    uint8_t buff[2];
    int32_t retVal;
    // opt4048_reg_thresh_exp_res_low_t threshReg;

    retVal = writeRegisterRegion(SFE_OPT4048_REGISTER_THRESH_L_EXP_RES, buff);

    if (retVal != 0)
        return false;

    return true;
}

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

bool QwOpt4048::setI2CBurst(bool enable)
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

bool QwOpt4048::getI2CBurst()
{
    uint8_t buff[2];
    opt4048_reg_int_control_t intReg;

    readRegisterRegion(SFE_OPT4048_REGISTER_INT_CONTROL, buff);

    intReg.word = buff[0] << 8;
    intReg.word |= buff[1];

    if (intReg.i2c_burst != 1)
        return false;

    return true;
}

void QwOpt4048::setCRC(bool enable)
{
    if (enable)
        crcEnabled = true;
    else
        crcEnabled = false;
}

uint32_t QwOpt4048::getADCCh0()
{
    uint8_t buff[4];
    uint32_t adcCode;
    uint32_t mantissa;
    opt4048_reg_exp_res_ch0_t adcReg;
    opt4048_reg_res_cnt_crc_ch0_t adc1Reg;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH0, buff, 4);

    adcReg.word = buff[0] << 8;
    adcReg.word |= buff[1];
    adc1Reg.word = buff[2] << 8;
    adc1Reg.word |= buff[3];

    mantissa = (uint32_t)adcReg.result_msb_ch0 << 8;
    mantissa |= adc1Reg.result_lsb_ch0;

    adcCode = mantissa << adcReg.exponent_ch0;

    return adcCode;
}

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

    mantissa = (uint32_t)adcReg.result_msb_ch1 << 8;
    mantissa |= adc1Reg.result_lsb_ch1;
    adcCode = mantissa << adcReg.exponent_ch1;

    return adcCode;
}

uint32_t QwOpt4048::getADCCh2()
{

    uint8_t buff[4];
    uint32_t adcCode;
    uint32_t mantissa;
    opt4048_reg_exp_res_ch2_t adcReg;
    opt4048_reg_res_cnt_crc_ch2_t adc1Reg;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH2, buff, 4);

    adcReg.word = buff[0] << 8;
    adcReg.word |= buff[1];
    adc1Reg.word = buff[2] << 8;
    adc1Reg.word |= buff[3];

    mantissa = (uint32_t)adcReg.result_msb_ch2 << 8;
    mantissa |= adc1Reg.result_lsb_ch2;

    adcCode = mantissa << adcReg.exponent_ch2;

    return adcCode;
}

uint32_t QwOpt4048::getADCCh3()
{

    uint8_t buff[4];
    uint32_t adcCode;
    uint32_t mantissa;
    opt4048_reg_exp_res_ch3_t adcReg;
    opt4048_reg_res_cnt_crc_ch3_t adc1Reg;

    readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH3, buff, 4);

    adcReg.word = buff[0] << 8;
    adcReg.word |= buff[1];
    adc1Reg.word = buff[2] << 8;
    adc1Reg.word |= buff[3];

    mantissa = (uint32_t)adcReg.result_msb_ch3 << 8;
    mantissa |= adc1Reg.result_lsb_ch3;

    adcCode = mantissa << adcReg.exponent_ch3;

    return adcCode;
}

sfe_color_t QwOpt4048::getAllADC()
{

    sfe_color_t color;

    color.red = getADCCh0();
    color.green = getADCCh1();
    color.blue = getADCCh2();
    color.white = getADCCh3();

    return color;
}

bool QwOpt4048::getAllChannelData(sfe_color_t *color)
{
    int32_t retVal;
    uint8_t buff[16];
    uint32_t mantissaCh0;
    uint32_t mantissaCh1;
    uint32_t mantissaCh2;
    uint32_t mantissaCh3;
    uint32_t adcCodeCh0;
    uint32_t adcCodeCh1;
    uint32_t adcCodeCh2;
    uint32_t adcCodeCh3;

    opt4048_reg_exp_res_ch0_t adc0MSB;
    opt4048_reg_res_cnt_crc_ch0_t adc0LSB;
    opt4048_reg_exp_res_ch1_t adc1MSB;
    opt4048_reg_res_cnt_crc_ch1_t adc1LSB;
    opt4048_reg_exp_res_ch2_t adc2MSB;
    opt4048_reg_res_cnt_crc_ch2_t adc2LSB;
    opt4048_reg_exp_res_ch3_t adc3MSB;
    opt4048_reg_res_cnt_crc_ch3_t adc3LSB;

    retVal = readRegisterRegion(SFE_OPT4048_REGISTER_EXP_RES_CH0, buff, 16);

    if (retVal != 0)
        return false;

    adc0MSB.word = buff[0] << 8;
    adc0MSB.word |= buff[1];
    adc0LSB.word = buff[2] << 8;
    adc0LSB.word |= buff[3];

    adc1MSB.word = buff[4] << 8;
    adc1MSB.word |= buff[5];
    adc1LSB.word = buff[6] << 8;
    adc1LSB.word |= buff[7];

    adc2MSB.word = buff[8] << 8;
    adc2MSB.word |= buff[9];
    adc2LSB.word = buff[10] << 8;
    adc2LSB.word |= buff[11];

    adc3MSB.word = buff[12] << 8;
    adc3MSB.word |= buff[13];
    adc3LSB.word = buff[14] << 8;
    adc3LSB.word |= buff[15];

    mantissaCh0 = (uint32_t)adc0MSB.result_msb_ch0 << 8;
    mantissaCh0 |= adc0LSB.result_lsb_ch0;
    adcCodeCh0 = mantissaCh0 << adc0MSB.exponent_ch0;

    mantissaCh1 = (uint32_t)adc1MSB.result_msb_ch1 << 8;
    mantissaCh1 |= adc1LSB.result_lsb_ch1;
    adcCodeCh1 = mantissaCh1 << adc1MSB.exponent_ch1;

    mantissaCh2 = (uint32_t)adc2MSB.result_msb_ch2 << 8;
    mantissaCh2 |= adc2LSB.result_lsb_ch2;
    adcCodeCh2 = mantissaCh2 << adc2MSB.exponent_ch2;

    mantissaCh3 = (uint32_t)adc3MSB.result_msb_ch3 << 8;
    mantissaCh3 |= adc3LSB.result_lsb_ch3;
    adcCodeCh3 = mantissaCh3 << adc3MSB.exponent_ch3;

    color->red = adcCodeCh0;
    color->green = adcCodeCh1;
    color->blue = adcCodeCh2;
    color->white = adcCodeCh3;

    color->counterR = adc0LSB.counter_ch0;
    color->counterG = adc1LSB.counter_ch1;
    color->counterR = adc2LSB.counter_ch2;
    color->counterR = adc3LSB.counter_ch3;

    color->CRCR = adc0LSB.crc_ch0;
    color->CRCG = adc1LSB.crc_ch1;
    color->CRCB = adc2LSB.crc_ch2;
    color->CRCW = adc3LSB.crc_ch3;

    return true;
}

bool QwOpt4048::calculateCRC(uint32_t mantissa, uint8_t expon, uint8_t crc)
{

    if (!crcEnabled)
        return false;

    mantissaBits mBits;
    exponBits exBits;
    crcBits cBits;
    crcBits compareAgainst;

    mBits.word = mantissa;
    exBits.byte = expon;
    cBits.byte = crc;

    compareAgainst.bit0 = exBits.byte xor mantissa xor cBits.byte;

    compareAgainst.bit1 = cBits.bit1 xor cBits.bit3 xor mBits.bit1 xor mBits.bit3 xor mBits.bit5 xor mBits.bit7 xor
                          mBits.bit9 xor mBits.bit11 xor mBits.bit13 xor mBits.bit15 xor mBits.bit17 xor mBits.bit19 xor
                          exBits.bit1 xor exBits.bit3;

    compareAgainst.bit2 =
        cBits.bit3 xor mBits.bit3 xor mBits.bit7 xor mBits.bit11 xor mBits.bit16 xor mBits.bit18 xor exBits.bit3;

    compareAgainst.bit3 = mBits.bit3 xor mBits.bit11 xor mBits.bit19;

    if (compareAgainst.byte == crc)
        return true;

    return false;
}

uint32_t QwOpt4048::getLux()
{
    uint32_t adcCh1;
    uint32_t lux;

    adcCh1 = getADCCh1();
    lux = adcCh1 * cieMatrix[1][3];

    return lux;
}

double QwOpt4048::getCIEx()
{
    double x = 0;
    double y = 0;
    double z = 0;
    double CIEx;
    static sfe_color_t color;

    getAllChannelData(&color);

    x += color.red * cieMatrix[0][0];
    x += color.green * cieMatrix[1][0];
    x += color.blue * cieMatrix[2][0];

    y += color.red * cieMatrix[0][1];
    y += color.green * cieMatrix[1][1];
    y += color.blue * cieMatrix[2][1];

    z += color.red * cieMatrix[0][2];
    z += color.green * cieMatrix[1][2];
    z += color.blue * cieMatrix[2][2];

    CIEx = x / (x + y + z);

    return CIEx;
}

double QwOpt4048::getCIEy()
{
    double x = 0;
    double y = 0;
    double z = 0;
    double CIEy;
    sfe_color_t color;

    getAllChannelData(&color);

    x += color.red * cieMatrix[0][0];
    x += color.green * cieMatrix[1][0];
    x += color.blue * cieMatrix[2][0];

    y += color.red * cieMatrix[0][1];
    y += color.green * cieMatrix[1][1];
    y += color.blue * cieMatrix[2][1];

    z += color.red * cieMatrix[0][2];
    z += color.green * cieMatrix[1][2];
    z += color.blue * cieMatrix[2][2];

    CIEy = y / (x + y + z);

    return CIEy;
}

double QwOpt4048::getCCT()
{
    double CIEx;
    double CIEy;
    double CCT;

    CIEx = getCIEx();
    CIEy = getCIEy();

    double n = (CIEx - 0.3320) / (0.1858 - CIEy);

    // Formula can be found under the CCT section in the datasheet.
    CCT = 437 * pow(n, 3) + 3601 * pow(n, 2) + 6861 * n + 5517;

    return CCT;
}
