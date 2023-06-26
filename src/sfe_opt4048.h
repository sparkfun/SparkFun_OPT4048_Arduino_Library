#pragma once
#include "OPT4048_Registers.h"
#include "sfe_bus.h"
#include <Math.h>
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

#define OPT4048_ERROR_NONE 0
#define OPT4048_ERROR_I2C -1
#define OPT4048_ERROR_PARAM -2

#define OPT_MATRIX_ROWS 4
#define OPT_MATRIX_COLS 4

#define OPT4048_DEVICE_ID 0x2108

class QwOpt4048
{
  public:

    QwOpt4048() : _i2cAddress{0}  {};

    bool init();
    bool isConnected();
    uint16_t getDeviceID();

    void setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus, uint8_t i2cAddress);
    void setCommunicationBus(sfe_OPT4048::QwDeviceBus &theBus);

    int32_t writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length = 2);
    int32_t readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t numBytes = 2);

    ///////////////////////////////////////////////////////////////////Device Settings

    bool enableQwake(bool enable);
    bool getQwake();

    typedef enum
    {
        RANGE_2KLUX2 = 0x00,
        RANGE_4KLUX5,
        RANGE_9LUX,
        RANGE_18LUX,
        RANGE_36LUX,
        RANGE_72LUX,
        RANGE_144LUX,
        RANGE_AUTO = 0x0C
    } opt4048_range_t;
    bool setRange(opt4048_range_t range);
    uint8_t getRange();

    typedef enum
    {
        CONVERSION_TIME_600US = 0x00,
        CONVERSION_TIME_1MS,
        CONVERSION_TIME_1MS8,
        CONVERSION_TIME_3MS4,
        CONVERSION_TIME_6MS5,
        CONVERSION_TIME_12MS7,
        CONVERSION_TIME_25MS,
        CONVERSION_TIME_50MS,
        CONVERSION_TIME_100MS,
        CONVERSION_TIME_200MS,
        CONVERSION_TIME_400MS,
        CONVERSION_TIME_800MS

    } opt4048_conversion_time_t;
    bool setConversionTime(opt4048_conversion_time_t time);
    uint8_t getConversionTime();

    typedef enum
    {
        OPERATION_MODE_POWER_DOWN = 0x00,
        OPERATION_MODE_AUTO_ONE_SHOT,
        OPERATION_MODE_ONE_SHOT,
        OPERATION_MODE_CONTINUOUS

    } opt4048_operation_mode_t;
    bool setOperationMode(opt4048_operation_mode_t mode);
    uint8_t getOperationMode();

    bool enableIntLatch(bool enable);
    bool getIntLatch();

    bool enableIntActiveHigh(bool enable);
    bool getIntPolarity();

    typedef enum
    {
        FAULT_COUNT_1 = 0x00,
        FAULT_COUNT_2,
        FAULT_COUNT_4,
        FAULT_COUNT_8
    } opt4048_fault_count_t;
    bool setFaultCount(opt4048_fault_count_t count);
    uint8_t getFaultCount();

    typedef enum
    {
        THRESH_CHANNEL_CH0 = 0x00,
        THRESH_CHANNEL_CH1,
        THRESH_CHANNEL_CH2,
        THRESH_CHANNEL_CH3
    } opt4048_threshold_channel_t;
    bool setThresholdChannel(opt4048_threshold_channel_t channel);
    uint8_t getThresholdChannel();

    uint16_t getThresholdHigh();
    uint16_t getThresholdLow();

    void enableCRC(bool enable);

    ///////////////////////////////////////////////////////////////////Interrupt Settings
    bool enableIntInput(bool enable);
    bool getIntInputEnable();

    typedef enum
    {
        INT_SMBUS_ALERT = 0x00,
        INT_DR_NEXT_CHANNEL,
        INT_DR_ALL_CHANNELS = 0x03
    } opt4048_mechanism_t;
    bool setIntMechanism(opt4048_mechanism_t mechanism);
    uint8_t getIntMechanism();

    bool enableI2CBurst(bool enable);
    bool getI2CBurst();

    bool setFlag(opt4048_reg_control_t flag);
    uint8_t getFlag();

    bool enableOverloadFlag(bool enable);
    bool enableConvReadyFlag(bool enable);
    bool enableTooBrightFlag(bool enable);
    bool enableTooDimFlag(bool enable);

    ///////////////////////////////////////////////////////////////////Color Information
    uint32_t getADCCh0();
    uint32_t getADCCh1();
    uint32_t getADCCh2();
    uint32_t getADCCh3();
    sfe_color_t getAllChannels();
    bool getAllChannelData(sfe_color_t *color);
    uint8_t calculateCRC(uint32_t manitssa, uint8_t expon, uint8_t crc);

    uint32_t getLux();
    uint32_t getCIEx();
    uint32_t getCIEy();
    uint32_t getCCT();

  private:
    sfe_OPT4048::QwDeviceBus *_sfeBus;
    uint8_t _i2cAddress;
    bool crcEnabled = false;

    // Table in 9.2.4 of Datasheet for calculating CIE x and y, and Lux.
    const long double cieMatrix[OPT_MATRIX_ROWS][OPT_MATRIX_COLS] = {
        {pow(2.34802002, -4), pow(-1.89652390, -5), pow(1.20811684, -5), 0},
        {pow(4.07467441, -5), pow(1.98958202, -4), pow(-1.58848114, -5), pow(2.15, -3)},
        {pow(8.28619404, -5), pow(-1.69739553, -5), pow(6.74021520, -4), 0},
        {0, 0, 0, 0}};
};
