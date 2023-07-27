/*
Example 4 - This example shows some of the examples. 

This example shows the various settings for the OPT4048 and how to set and read them. 

Written by Elias Santistevan @ SparkFun Electronics, July 2023

Products:
    Qwiic 1x1: https://www.sparkfun.com/products/22638
    Qwiic Mini: https://www.sparkfun.com/products/22639

Repository:
    https://github.com/sparkfun/SparkFun_OPT4048_Arduino_Library

SparkFun code, firmware, and software is released under the MIT 
License	(http://opensource.org/licenses/MIT).
*/

#include "SparkFun_OPT4048.h"
#include <Wire.h>

SparkFun_OPT4048 myColor;

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 4 OPT4048 Advanced Settings");

    Wire.begin();

    if (!myColor.begin()) {
        Serial.println("OPT4048 not detected- check wiring or that your I2C address is correct!");
        while (1) ;
    }



    /////////////////////////////////////////////General Settings
    /*
     RANGE_2KLUX2,
     RANGE_4KLUX5,
     RANGE_9LUX,
     RANGE_18LUX,
     RANGE_36LUX,
     RANGE_72LUX,
     RANGE_144LUX,
     RANGE_AUTO
     A higher color range will result in a lower resolution.
     The RANGE_AUTO option will automatically select the best 
     range for the current light conditions.
    */
    myColor.setRange(RANGE_2KLUX2);
    Serial.print("Range set to: ");
    Serial.println(myColor.getRange());
    //

    /*
     CONVERSION_TIME_600US,
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
     A higher conversion time will result in more precise readings. 
     For color sensing, having the highest converstion time is suggested.
    */
    myColor.setConversionTime(CONVERSION_TIME_800MS);
    Serial.print("Conversion time set to:");
    Serial.println(myColor.getConversionTime());

    /*
     OPERATION_MODE_POWER_DOWN,
     OPERATION_MODE_AUTO_ONE_SHOT,
     OPERATION_MODE_ONE_SHOT,
     OPERATION_MODE_CONTINUOUS
    */
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);
    Serial.print("Conversion time set to:");
    Serial.println(myColor.getOperationMode());

    
   // The Quick wake setting changes the behavior of the chip while in power down mode: 
   // Not all of the circuitry will be powered down. 
   // myColor.enableQwake();
    Serial.println("Ready to go!");
}


void loop()
{
    Serial.print("CIEx");
    Serial.print(myColor.getCIEx());
    Serial.print("CIEy");
    Serial.print(myColor.getCIEy());
    Serial.print("CCT");
    Serial.println(myColor.getCCT());
    // Delay time is set to the conversion time * number of channels
    // You need three channels for color sensing @ 800ms conversion time = 3200ms.
    delay(3200);
}
