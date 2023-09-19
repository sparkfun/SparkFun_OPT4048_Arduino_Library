#include "SparkFun_OPT4048.h"
#include "lp55231.h"
#include <Wire.h>

#define ROYAL_BLUE 0
#define LIGHT_BLUE 1
#define CYAN 2
#define GREEN 3
#define YELLOW 4
#define ORANGE 5
#define LIGHT_RED 6
#define BRIGHT_RED 7
#define FAR_RED    8

#define LED_ADDRESS 0x35   
#define ARRAY_SIZE 9   
#define TAIL 8   
#define HEAD 0   

SparkFun_OPT4048 myColor;
Lp55231 ledChip(LED_ADDRESS);

const int channel[ARRAY_SIZE] = {2,1,7,3,4,8,5,6,9};
int arrayPos = 0; 

unsigned long lastTime;

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");

    // Usng SPI for the SD Card.
    Wire.begin();

    if (!myColor.begin()) 
    {
        Serial.println("OPT4048 not detected. Please check wiring. Freezing...");
        while (1) 
            ;
    }

    //ledChip.Begin();
    //ledChip.Enable();
    //ledChip.SetChargePumpMode(CP_BYPASS);

    //delay(100);

    //for(int i = 0; i < 9; i++) 
    //    ledChip.SetLogBrightness(i, true);

    myColor.setRange(RANGE_2KLUX2);
    myColor.setConversionTime(CONVERSION_TIME_800MS);
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);

    lastTime = millis();

    Serial.println("-------------------------------------");
    Serial.println("Enter a number between 0-8");
    Serial.println("Make sure to add 'NO LINE ENDING'!!");
    Serial.println("-------------------------------------");
    delay(3000);


}


void loop()
{
    if(arrayPos == HEAD)
    {
        ledChip.SetChannelPWM(channel[TAIL]-1, 0);
        ledChip.SetChannelPWM(channel[arrayPos]-1, 50);
    }

    ledChip.SetChannelPWM(channel[arrayPos]-2, 0);
    ledChip.SetChannelPWM(channel[arrayPos]-1, 50);
    Serial.print("CIEx: ");
    Serial.print(myColor.getCIEx());
    Serial.print(" CIEy: ");
    Serial.print(myColor.getCIEy());
    Serial.print(" Color, ");
    Serial.println(arrayPos);

    delay(200);
}

void serialEvent()
{
    int entry = Serial.parseInt();
    switch(entry)
    {
        case 0: 
            arrayPos = 0;
            break;
        case 1: 
            arrayPos = 1;
            break;
        case 2: 
            arrayPos = 2;
            break;
        case 3: 
            arrayPos = 3;
            break;
        case 4: 
            arrayPos = 4;
            break;
        case 5: 
            arrayPos = 5;
            break;
        case 6: 
            arrayPos = 6;
            break;
        case 7: 
            arrayPos = 7;
            break;
        case 8: 
            arrayPos = 8;
            break;
        default:
            Serial.println("Enter a number between 0-8");
    }

    return;
}
