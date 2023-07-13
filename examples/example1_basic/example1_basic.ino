#include "SparkFun_OPT4048.h"
#include "lp55231.h"
#include <Wire.h>

SparkFun_OPT4048 myColor;
Lp55231 ledChip(0x35);

int channel[] = {2,1,7,3,4,8,5,6,9};

#define ROYAL_BLUE 0
#define LIGHT_BLUE 1
#define CYAN 2
#define GREEN 3
#define YELLOW 4
#define ORANGE 5
#define LIGHT_RED 6
#define BRIGHT_RED 7
#define FAR_RED    8

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");
    pinMode(13, OUTPUT);
    Wire.begin();

    if (!myColor.begin())
    {
        Serial.println("OPT4048 not detected. Please check wiring. Freezing...");
        while (1) ;
    }

    ledChip.Begin();
    ledChip.Enable();
    ledChip.SetChargePumpMode(CP_BYPASS);

    delay(500);

    for(uint8_t i = 0; i < 9; i++)
    {
        ledChip.SetLogBrightness(i, true);
    }

    myColor.setRange(RANGE_2KLUX2);
    //Serial.println(myColor.getRange());
    myColor.setConversionTime(CONVERSION_TIME_800MS);
    //Serial.println(myColor.getConversionTime());
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);

    Serial.println("Great");
}

void loop()
{

    // Full brightness 255
    // Array is as follows:[blue]
    for(int i = 0; i < FAR_RED; i++)
    {
        ledChip.SetChannelPWM(channel[i]-1, 50);

        Serial.printf("Color: %d \n", i);

        for(int j = 0; j < 3; j++)
        {
            delay(3200);
            Serial.printf("\nCIEx: %0.4f, CIEy %0.4f, Sample: %d\n", 
                            myColor.getCIEx(), myColor.getCIEy(), j+1);
            // Four times converstion time
        }

        ledChip.SetChannelPWM(channel[i]-1, 0);

    }
}
