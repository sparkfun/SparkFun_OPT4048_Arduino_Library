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


    Serial.println("Great!");
    Serial.println("Press any key in the Serial Monitor to begin.");

    // Press someting to begin the test. 
    while(!(Serial.available() > 0))
    {
        delay(10);
    }
    
    Serial.println("Away we go!");


}


void loop()
{

    Serial.println("Measurements started.");

    //for(int color = 0; color <= FAR_RED; color++) {

    //    ledChip.SetChannelPWM(channel[color]-1, 50);

    //    // Color
    //    Serial.print("Color, ");
    //    Serial.println(color);

    //   // for(int sample = 0; sample < 3; sample++) {
    //    //    delay(3200);

    //    ledChip.SetChannelPWM(channel[color]-1, 0);

    //}

    Serial.println(arrayPos);
}

void serialEvent()
{
    int entry; 
    entry = Serial.parseInt();

    if(entry == 1)
    {        
        if(arrayPos >= ARRAY_SIZE)
            arrayPos = 0; 
            return;

        arrayPos = arrayPos + 1;
    }

    return;
}
