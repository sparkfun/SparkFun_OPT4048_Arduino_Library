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

   // myColor.enableQwake(true);
   // Serial.println(myColor.getQwake(), HEX);
   // myColor.enableQwake(false);
   // Serial.println(myColor.getQwake(), HEX);
   // 
    myColor.setRange(RANGE_144LUX);
    Serial.println(myColor.getRange(), HEX);
    myColor.setConversionTime(CONVERSION_TIME_200MS);
    Serial.println(myColor.getConversionTime(), HEX);
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);

    //myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);
    //Serial.println(myColor.getOperationMode(), HEX);

    //Serial.println("Latch: ");
    //myColor.enableIntLatch(true);
    //Serial.println(myColor.getIntLatch(), HEX);

    ////WHAT.
    //myColor.setFaultCount(FAULT_COUNT_2);
    //Serial.println(myColor.getFaultCount(), HEX);

    //myColor.enableIntActiveHigh(true);
    //Serial.println(myColor.getIntActiveHigh(), HEX);
 
    //myColor.setThresholdChannel(THRESH_CHANNEL_CH3);
    //Serial.println(myColor.getThresholdChannel(), HEX);
 
   // uint16_t getThresholdHigh();
   // uint16_t getThresholdLow();

   // void enableCRC(bool enable);

   //myColor.enableIntInput(true);
   //Serial.println(myColor.getIntInputEnable(), HEX);

   //myColor.setIntMechanism(INT_DR_ALL_CHANNELS);
   //Serial.println(myColor.getIntMechanism(),HEX);

   //myColor.enableI2CBurst(true);
   //Serial.println(myColor.getI2CBurst(), HEX);

   // uint8_t getFlag();
   //Serial.println(myColor.getOverloadFlag(), HEX);
   //Serial.println(myColor.getConvReadyFlag(),HEX);
   //Serial.println(myColor.getTooBrightFlag(),HEX);
   //Serial.println(myColor.getTooDimFlag(),HEX);
   // ///////////////////////////////////////////////////////////////////Color Information
   // sfe_color_t getAllADC();
   // bool getAllChannelData(sfe_color_t *color);
   // uint8_t calculateCRC(uint32_t manitssa, uint8_t expon, uint8_t crc);

   // uint32_t getLux();
   // uint32_t getCIEx();
   // uint32_t getCIEy();
   // uint32_t getCCT();

    Serial.println("Great");
}

void loop()
{
   Serial.println(myColor.getADCCh0());
   Serial.println(myColor.getADCCh1());
   Serial.println(myColor.getADCCh2());
   Serial.println(myColor.getADCCh3());
   delay(200);
}
