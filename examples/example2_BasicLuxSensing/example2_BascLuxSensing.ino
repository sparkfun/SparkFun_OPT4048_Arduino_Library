/*
Example 1 - Basic Color Sensing

This example shows the basic operation of the OPT4048 Color Sensor
for sensing light intensity.

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

    myColor.setBasicSetup();

    Serial.println("Ready to go!");
}


void loop()
{
    Serial.print("Lux:");
    Serial.print(myColor.getLux());
    // Delay time is set to the conversion time * number of channels
    // You only need one channel for sensing light intensity @ 200ms conversion time = 200ms. 
    delay(200);
}
