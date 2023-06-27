#include "SparkFun_OPT4048.h"
#include <Wire.h>

SparkFun_OPT4048 myColor;

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");

    Wire.begin();

    if (!myColor.begin())
    {
        Serial.println("OPT4048 not detected. Please check wiring. Freezing...");
        while (1) ;
    }

    myColor.enableQwake(true);
    Serial.println(myColor.getQwake(), HEX);
    myColor.enableQwake(false);
    Serial.println(myColor.getQwake(), HEX);
   // 
   // bool setRange(opt4048_range_t range);
   // opt4048_range_t getRange();
   // bool setConversionTime(opt4048_conversion_time_t time);
   // opt4048_conversion_time_t getConversionTime();
   // bool setOperationMode(opt4048_operation_mode_t mode);
   // opt4048_operation_mode_t getOperationMode();
   // bool enableIntLatch(bool enable);
   // bool getIntLatch();
   // bool setFaultCount(opt4048_fault_count_t count);
   // opt4048_fault_count_t getFaultCount();

   // bool enableIntActiveHigh(bool enable);
   // bool getIntPolarity();
   // bool setThresholdChannel(opt4048_threshold_channel_t channel);
   // opt4048_threshold_channel_t getThresholdChannel();

   // uint16_t getThresholdHigh();
   // uint16_t getThresholdLow();

   // void enableCRC(bool enable);

   // bool enableIntInput(bool enable);
   // bool getIntInputEnable();
   // bool enableIntInput(bool enable);
   // bool getIntInputEnable();
   // bool setIntMechanism(opt4048_mechanism_t mechanism);
   // opt4048_mechanism_t getIntMechanism();

   // bool enableI2CBurst(bool enable);
   // bool getI2CBurst();

   // bool setFlag(opt4048_reg_flags_t flag);
   // uint8_t getFlag();

   // bool enableOverloadFlag(bool enable);
   // bool enableConvReadyFlag(bool enable);
   // bool enableTooBrightFlag(bool enable);
   // bool enableTooDimFlag(bool enable);
   // ///////////////////////////////////////////////////////////////////Color Information
   // uint32_t getADCCh0();
   // uint32_t getADCCh1();
   // uint32_t getADCCh2();
   // uint32_t getADCCh3();
   // sfe_color_t getAllADC();
   // bool getAllChannelData(sfe_color_t *color);
   // uint8_t calculateCRC(uint32_t manitssa, uint8_t expon, uint8_t crc);

   // uint32_t getLux();
   // uint32_t getCIEx();
   // uint32_t getCIEy();
   // uint32_t getCCT();

    Serial.println("Great");
    while(1);
}

void loop()
{
}
