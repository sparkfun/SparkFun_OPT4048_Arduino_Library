/*
Example 3 - Color Warmth

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
    Serial.println("OPT4048 Example 1 Basic Color Sensing.");

    Wire.begin();

    if (!myColor.begin()) {
        Serial.println("OPT4048 not detected- check wiring or that your I2C address is correct!");
        while (1) ;
    }

    /// RANGE_2KLUX2,
    /// RANGE_4KLUX5,
    /// RANGE_9LUX,
    /// RANGE_18LUX,
    /// RANGE_36LUX,
    /// RANGE_72LUX,
    /// RANGE_144LUX,
    /// RANGE_AUTO
    // A higher color range will result in a lower resolution.
    // The RANGE_AUTO option will automatically select the best 
    // range for the current light conditions.
    myColor.setRange(RANGE_36LUX);
    Serial.print("Range set to: ");
    Serial.println(myColor.getRange());

    /// CONVERSION_TIME_600US,
    /// CONVERSION_TIME_1MS,
    /// CONVERSION_TIME_1MS8,
    /// CONVERSION_TIME_3MS4,
    /// CONVERSION_TIME_6MS5,
    /// CONVERSION_TIME_12MS7,
    /// CONVERSION_TIME_25MS,
    /// CONVERSION_TIME_50MS,
    /// CONVERSION_TIME_100MS,
    /// CONVERSION_TIME_200MS,
    /// CONVERSION_TIME_400MS,
    /// CONVERSION_TIME_800MS
    // A higher conversion time will result in more precise readings. 
    // For color sensing, having the highest converstion time is suggested.
    myColor.setConversionTime(CONVERSION_TIME_200MS);
    Serial.print("Conversion time set to:");
    Serial.println(myColor.getConversionTime());

    /// OPERATION_MODE_POWER_DOWN,
    /// OPERATION_MODE_AUTO_ONE_SHOT,
    /// OPERATION_MODE_ONE_SHOT,
    /// OPERATION_MODE_CONTINUOUS
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);


    Serial.println("Ready to go!");
}


void loop()
{
    Serial.print("Color Warmth: ");
    Serial.print(myColor.getCCT());
    // Delay time is set to the conversion time * number of channels
    // You need three channels for color sensing @ 200ms conversion time = 600ms.
    delay(600);
}
