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

#define OPT_MATRIX_ROWS 4
#define OPT_MATRIX_COLS 4

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

    bool setRange(opt4048_range_t range);
    opt4048_range_t getRange();

    bool setConversionTime(opt4048_conversion_time_t time);
    opt4048_conversion_time_t getConversionTime();

    bool setOperationMode(opt4048_operation_mode_t mode);
    opt4048_operation_mode_t getOperationMode();

    bool enableIntLatch(bool enable);
    bool getIntLatch();

    bool enableIntActiveHigh(bool enable);
    bool getIntActiveHigh();

    bool setFaultCount(opt4048_fault_count_t count);
    opt4048_fault_count_t getFaultCount();

    bool setThresholdChannel(opt4048_threshold_channel_t channel);
    opt4048_threshold_channel_t getThresholdChannel();

    bool setThresholdHigh(float thresh);
    uint16_t getThresholdHigh();
    bool setThresholdLow(float thresh);
    uint16_t getThresholdLow();

    void enableCRC(bool enable);

    ///////////////////////////////////////////////////////////////////Interrupt Settings
    bool enableIntInput(bool enable);
    bool getIntInputEnable();

    bool setIntMechanism(opt4048_mechanism_t mechanism);
    opt4048_mechanism_t getIntMechanism();

    bool enableI2CBurst(bool enable);
    bool getI2CBurst();

    opt4048_reg_flags_t getAllFlags();
    bool getOverloadFlag();
    bool getConvReadyFlag();
    bool getTooBrightFlag();
    bool getTooDimFlag();

    ///////////////////////////////////////////////////////////////////Color Information
    uint32_t getADCCh0();
    uint32_t getADCCh1();
    uint32_t getADCCh2();
    uint32_t getADCCh3();
    sfe_color_t getAllADC();
    bool getAllChannelData(sfe_color_t *color);
    uint8_t calculateCRC(uint32_t manitssa, uint8_t expon, uint8_t crc);

    uint32_t getLux();
    double getCIEx();
    double getCIEy();
    double getCCT();

  private:

    sfe_OPT4048::QwDeviceBus *_sfeBus;
    uint8_t _i2cAddress;
    bool crcEnabled = false;

    // Table in 9.2.4 of Datasheet for calculating CIE x and y, and Lux.
    const long double cieMatrix[OPT_MATRIX_ROWS][OPT_MATRIX_COLS] = {
        {pow(2.34892992, -4), pow(-1.89652390, -5), pow(1.20811684, -5), 0},
        {pow(4.07467441, -5), pow(1.98958202, -4), pow(-1.58848115, -5), pow(2.15, -3)},
        {pow(9.28619404, -5), pow(-1.69739553, -5), pow(6.74021520, -4), 0},
        {0, 0, 0, 0}};
};
