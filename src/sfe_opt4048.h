/*
sfe_opt4048.h

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

The following QwOpt4048 class defines the main main functionality for the OPT4048 IC. 
This file also includes the type definitions for function parameters as well as 
data types for the color data. 

*/
#pragma once
#include "OPT4048_Registers.h"
#include "sfe_bus.h"
#include <Wire.h>

/// @brief Struct used to store the color data from the OPT4048.
typedef struct
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t white;
    uint8_t counterR; // Sample counter
    uint8_t counterG;
    uint8_t counterB;
    uint8_t counterW;
    uint8_t CRCR;
    uint8_t CRCG;
    uint8_t CRCB;
    uint8_t CRCW;

} sfe_color_t;

/// @brief  Union used to re-calculate the CRC for optional double check.
typedef union {
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
    };
    uint8_t byte;
} crcBits;

/// @brief  Union used to re-calculate the CRC for optional double check.
typedef union {
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
    };
    uint8_t byte;
} exponBits;

/// @brief  Union used to re-calculate the CRC for optional double check.
typedef union {
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
        uint8_t bit8 : 1;
        uint8_t bit9 : 1;
        uint8_t bit10 : 1;
        uint8_t bit11 : 1;
        uint8_t bit12 : 1;
        uint8_t bit13 : 1;
        uint8_t bit14 : 1;
        uint8_t bit15 : 1;
        uint8_t bit16 : 1;
        uint8_t bit17 : 1;
        uint8_t bit18 : 1;
        uint8_t bit19 : 1;
    };
    uint32_t word;
} mantissaBits;

#define OPT_MATRIX_ROWS 4
#define OPT_MATRIX_COLS 4

class QwOpt4048
{
  public:
    QwOpt4048() : _sfeBus(nullptr) , _i2cAddress(0) {};

    /// @brief Sets the struct that interfaces with STMicroelectronic's C Library.
    /// @return true on successful execution.
    bool init();

    /// @brief Checks that the bus is connected with the OPT4048 by checking
    /// it's unique ID.
    /// @return True on successful execution.
    bool isConnected();

    /// @brief Retrieves the the device's ID: 0x24 for the OPT4048.
    /// @return Returns the unique ID.
    uint16_t getDeviceID();

    /// @brief Sets the pointer to the data bus for read and writes.
    /// @param theBus This parameter sets the the I2C hardware bus.
    /// @param i2cAddress The I2C address for the device.
    void setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus, uint8_t i2cAddress);

    /// @brief Sets the pointer to the data bus for read and writes.
    /// @param theBus This parameter sets the hardware bus.
    void setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus);

    /// @brief Writes to the data to the given register using the hardware data bus.
    /// @param  offset The register to write to.
    /// @param  data The data to write to the register.
    /// @param  length The number of writes
    /// @return The successful (0) or unsuccessful (-1) write to the given register.
    int32_t writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length = 2);

    /// @brief Reads data from the specified register using the set data bas.
    /// @param  offset The register to read from.
    /// @param  data The pointer to the value to store the value.
    /// @param  length The number of reads
    /// @return The successful (0) or unsuccessful (-1) read of the given register.
    int32_t readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t numBytes = 2);

    ///////////////////////////////////////////////////////////////////Device Settings

    /// @brief Sets the minimum of settings to get the board running.
    void setBasicSetup();

    /// @brief Sets the OPT4048's effective sensing range which will effect its resolution.
    /// @param range The range to set the device to.
    /// @return True on successful execution.
    bool setQwake(bool enable = true);
    
    /// @brief Retrieves the light range in lux of the OPT4048.
    /// @return The range of lux able to be measured.
    bool getQwake();

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
    bool setRange(opt4048_range_t range);
    
    /// @brief Retrieves the light range in lux of the OPT4048.
    /// @return The range of lux able to be measured.
    opt4048_range_t getRange();

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
    bool setConversionTime(opt4048_conversion_time_t time);

    /// @brief Retrieves the conversion time used for the ADC.
    /// @return The OPT4048 conversion time.
    opt4048_conversion_time_t getConversionTime();


    /// @brief Sets the OPT4048's operation mode.
    /// @param mode The mode to set the device to. Possible Values:
    ///   OPERATION_MODE_POWER_DOWN,
    ///   OPERATION_MODE_AUTO_ONE_SHOT,
    ///   OPERATION_MODE_ONE_SHOT,
    ///   OPERATION_MODE_CONTINUOUS
    /// @return
    bool setOperationMode(opt4048_operation_mode_t mode);

    /// @brief Retrieves the set operation mode.
    /// @return The OPT4048 conversion time.
    opt4048_operation_mode_t getOperationMode();

    /// @brief Changes the behavior of the interrupt from pin to latch.
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    bool setIntLatch(bool enable = true);

    /// @brief Checks if the interrupt is set to pulse or latch.
    /// @return True if set to latch, false if not.
    bool getIntLatch();

    /// @brief Sets the OPT4048's interrupt polarity.
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    bool setIntActiveHigh(bool enable = true);

    /// @brief Sets the OPT4048's interrupt polarity.
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    bool getIntActiveHigh();

    /// @brief Sets the number of faults (light values over or under) before an interrupt is triggered.
    /// @param count The number of faults to trigger an interrupt
    ///   FAULT_COUNT_1,
    ///   FAULT_COUNT_2,
    ///   FAULT_COUNT_4,
    ///   FAULT_COUNT_8
    /// @return True on successful execution.
    bool setFaultCount(opt4048_fault_count_t count);

    /// @brief Retrieves the number of faults (light values over or under) before 
    /// an interrupt is triggered.
    /// @return The fault count.
    opt4048_fault_count_t getFaultCount();

    /// @brief Sets the channel for threshold logic
    /// @param channel The channel to set the threshold logic to.
    ///   THRESH_CHANNEL_CH0,
    ///   THRESH_CHANNEL_CH1,
    ///   THRESH_CHANNEL_CH2,
    ///   THRESH_CHANNEL_CH3
    /// @return True on successful execution.
    bool setThresholdChannel(opt4048_threshold_channel_t channel);

    /// @brief Retrives the threshold channel.
    /// @return THe selected channel. 
    opt4048_threshold_channel_t getThresholdChannel();

    /// @brief Sets the Lux High Value threshold.
    /// @param thresh The value in float
    /// @return Returns the high threshold.
    bool setThresholdHigh(float thresh);
    
    /// @brief Retrieves the Lux High Value threshold.
    /// @return Returns the high threshold.
    uint16_t getThresholdHigh();

    /// @brief Sets the Lux Low Value threshold.
    /// @param thresh The value in float
    /// @return Returns the high threshold.
    bool setThresholdLow(float thresh);

    /// @brief Retrieves the Lux Low Value threshold.
    /// @return Returns the low threshold.
    uint16_t getThresholdLow();

    /// @brief Enable CRC for ADC calues
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    void setCRC(bool enable = true);

    ///////////////////////////////////////////////////////////////////Interrupt Settings
    /// @brief Changes the behavior of the interrupt pin to be an INPUT to trigger single shot.
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    bool setIntInput(bool enable = true);

    /// @brief Gets the interrupt input bit
    /// @return True if the interrupt is set to INPUT.
    bool getIntInputEnable();

    /// @brief Changes the behavior interrupt mechanism after the end of conversion
    /// @param mechanism The mechanism to set
    /// @return True on successful execution.
    bool setIntMechanism(opt4048_int_cfg_t mechanism);

    /// @brief Gets the interrupt mechanism for the OPT4048
    /// @return Returns the setd mechanism.
    opt4048_int_cfg_t getIntMechanism();

    /// @brief Enable register auto increment .
    /// @param set True to enable, false to disable.
    /// @return True on successful execution.
    bool setI2CBurst(bool enable = true);

    /// @brief Retrieves the I2C burst bit.
    /// @return True if I2C burst is setd, false otherwise.
    bool getI2CBurst();

    /// @brief Retrieves the flag register
    /// @return The contents of the flag register
    opt4048_reg_flags_t getAllFlags();

    /// @brief Checks the overload flag bit.
    /// @return True if the overload flag bit is set, false otherwise
    bool getOverloadFlag();

    /// @brief Checks the conversion ready flag bit.
    /// @return True if that flag bit is set, false otherwise
    bool getConvReadyFlag();

    /// @brief Checks the too bright flag bit.
    /// @return True if that flag bit is set, false otherwise
    bool getTooBrightFlag();

    /// @brief Checks the too dim flag bit.
    /// @return True if that flag bit is set, false otherwise
    bool getTooDimFlag();
    
    ///////////////////////////////////////////////////////////////////Color Information
    /// @brief Reads Channel Zero (Red)
    /// @return Returns the ADC value of Channel Zero
    uint32_t getADCCh0();

    /// @brief Reads Channel One (Green)
    /// @return Returns the ADC value of Channel One
    uint32_t getADCCh1();

    /// @brief Reads Channel Two (Blue)
    /// @return Returns the ADC value of Channel Two
    uint32_t getADCCh2();

    /// @brief Reads Channel Three (White)
    /// @return Returns the ADC value of Channel Three
    uint32_t getADCCh3();

    /// @brief Retrieves all ADC values for all channels: Red, Green, Blue, and White.
    /// @return Returns the ADC values of the channels.
    sfe_color_t getAllADC();

    /// @brief Retrieves all ADC values for all channels: Red, Green, Blue, and White, as well as the sample counter, and
    ///        the CRC value.
    /// @param color Pointer to the color struct to be populated with the channels values.
    /// @return Returns true on successful execution, false otherwise.
    bool getAllChannelData(sfe_color_t *color);

    /// @brief  Calculates the CRC for the OPT4048. Note that the OPT4048 does this already
    ///         but this is a way to double check the value.
    /// @param mantissa The mantissa value of the ADC
    /// @param exponent The exponent value of the ADC
    /// @param crc The CRC value of the ADC
    /// @return Returns the calculated CRC value.
    bool calculateCRC(uint32_t manitssa, uint8_t expon, uint8_t crc);

    /// @brief Retrieves the Lux value.
    /// @return Returns the Lux value of the sensor
    uint32_t getLux();

    /// @brief  Retrieves the CIE X value of the sensor.
    /// @return Returns the CIE X value of the sensor
    double getCIEx();

    /// @brief Retrieves the CIE Y value of the sensor.
    /// @return Returns the CIE Y value of the sensor
    double getCIEy();

    /// @brief Retrieves the Correlated Color Temperature (CCT) of the sensor.
    /// @return Returns the CCT of the sensor in Kelvin
    double getCCT();

  private:
    sfe_OPT4048::QwDeviceBus *_sfeBus;
    uint8_t _i2cAddress;
    bool crcEnabled = false;

    // Table in 9.2.4 of Datasheet for calculating CIE x and y, and Lux.
    const double cieMatrix[OPT_MATRIX_ROWS][OPT_MATRIX_COLS] = {
        {.000234892992, -.0000189652390, .0000120811684, 0},
        {.0000407467441, .000198958202, -.0000158848115, .00215},
        {.0000928619404, -.0000169739553, .000674021520, 0},
        {0, 0, 0, 0}};
};
