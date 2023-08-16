/*
Example 5 - Interrupts

This example shows the various interrupt settings and their uses. 

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

int interruptPin = 3; 

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 5 - Interrups.");

    pinMode(interruptPin, OUTPUT);

    Wire.begin();

    if (!myColor.begin()) {
        Serial.println("OPT4048 not detected- check wiring or that your I2C address is correct!");
        while (1) ;
    }

    // See Color Settings Example for functions for setting
    // converstion time, range, and mode. 
    myColor.setBasicSetup();

    // Basic usage: if interrupt is set to latched mode
    myColor.enableIntLatch();

    // Select the channel that will fire the interrupt
    // Lux values are generated in Channel One.
    myColor.setThresholdChannel(THRESH_CHANNEL_CH1);

    // Change the interrupt direction to active HIGH. 
    //myColor.enableIntActiveHigh();

    // Change the interrupt to an INPUT to trigger measurements
    // set operation mode to one shot mode in this case. 
    // myColor.enableIntInput();

    Serial.println("Ready to go!");
}


void loop()
{
    if(digitalRead(interruptPin) == LOW)
    {
        Serial.print("Lux Value: ");
        Serial.println(myColor.getLux());
    }
    // Delay time is set to the conversion time * number of channels
    // You need three channels for color sensing @ 200ms conversion time = 600ms.
    delay(200);
}
