#include "OPT4048_Registers.h"
#include "sfe_bus.h"
#include <Wire.h>

typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t l;
    uint8_t counter; // Sample counter
    uint8_t CRC;

} sfe_color_t;

#define OPT4048_ERROR_NONE 0
#define OPT4048_ERROR_I2C -1
#define OPT4048_ERROR_PARAM -2

#define OPT4048_DEVICE_ID 0x2108

class QwOpt4048
{
  public:
    QwOpt4048() : _i2cAddress{0}, _i2cPort{nullptr} {};

    bool init();
    bool isConnected();
    int8_t getErrorCode();
    uint16_t getDeviceID();

    void setCommunicationBus(sfe_OPT4048::QwDeviceBus *theBus, uint8_t i2cAddress);

    int32_t writeRegisterRegion(uint8_t address, uint8_t offset, const uint8_t *data, uint16_t length = 2);
    int32_t readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes = 2);

    ///////////////////////////////////////////////////////////////////Device Settings
    
    bool enableQwake(bool enable);
    bool getQwake();

    typedef enum
    {
      RANGE_2KLUX2= 0x00,
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
    bool getOperationMode(opt4048_operation_mode_t *mode);

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
    bool getFaultCount(opt4048_fault_count_t *count);

    myClass::int8_t getThresholdHigh()
    {
      error = retu
      if(error)
      return OPT4048_ERROR_I2C
    }

    typedef enum
    {
      THRESH_CHANNEL_CH0 = 0x00,
      THRESH_CHANNEL_CH1,
      THRESH_CHANNEL_CH2,
      THRESH_CHANNEL_CH3,
    }opt4048_threshold_channel_t;
    bool setThresholdChannel(opt4048_threshold_channel_t channel);
    uint8_t setThresholdChannel();
    bool getThresholdChannel(opt4048_threshold_channel_t *channel);

    bool getThresholdHigh(opt4048_exp_res_reg_high_t *threshold);
    bool getThresholdLow(opt4048_exp_res_reg_low_t *threshold);

    bool enableCRC(bool enable);

    ///////////////////////////////////////////////////////////////////Interrupt Settings
    bool enableIntInput(bool enable);
    bool getIntInputEnable();

    typedef enum
    {
      INT_SMBUS_ALERT = 0x00,
      INT_DR_NEXT_CHANNEL
      INT_DR_ALL_CHANNELS = 0x03
    } opt4048_mechanism_t;
    bool setIntMechanism(opt4048_mechanism_t mechanism);
    bool getIntMechanism(opt4048_mechanism_t *mechanism);

    bool enableI2CBurst(bool enable);
    bool getI2CBurst();

    typedef enum
    {
      FLAG_LOW = 0x00,
      FLAG_HIGH, 
      CONVERSION_READY_FLAG,
      OVERLOAD_FLAG
    }opt4048_flags_t
    bool setFlag(opt4048_flags_t flag);
    bool getFlag(opt4048_flags_t *flag);

    bool enableOverloadFlag(bool enable);
    bool enableConvReadyFlag(bool enable);
    bool enableTooBrightFlag(bool enable);
    bool enableTooDimFlag(bool enable);

    ///////////////////////////////////////////////////////////////////Color Information
    bool getADCCh0(uint32_t *chan0);
    bool getADCCh1(uint32_t *chan1);
    bool getADCCh2(uint32_t *chan2);
    bool getADCCh3(uint32_t *chan3);

    bool getLux(uint32_t *lux);

    bool getCIEx(uint32_t *CIEx);
    bool getCIEy(uint32_t *CIEx);

    bool getCCT(uint32_t *CCT);

  private:
    sfe_OPT4048::QwDeviceBus *_sfeBus;
    uint8_t _i2cAddress;
    bool crcEnabled = false;
};
