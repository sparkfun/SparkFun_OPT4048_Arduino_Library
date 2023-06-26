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
}

void loop()
{
    Serial.println("ping");
}