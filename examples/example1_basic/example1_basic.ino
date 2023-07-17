/*
    Color data is filed comma-separated as follows:
    "Color tag, CIEx, CIEy, Sample number"
*/

#include <SD.h>
#include "SparkFun_OPT4048.h"
#include "lp55231.h"
#include <Wire.h>
#include <SPI.h>

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

SparkFun_OPT4048 myColor;
Lp55231 ledChip(LED_ADDRESS);

const int channel[] = {2,1,7,3,4,8,5,6,9};
const int chipSelect = 28;
char intContents[100] = {};

unsigned long lastTime;
File myFile; 

bool testSD()
{
    
    myFile = SD.open("test.txt", FILE_WRITE);

    if(!myFile)
        return false;

    if(myFile) {

        myFile.println(21);
        myFile.close(); 
    }

    delay(500);

    myFile = SD.open("test.txt", FILE_READ);

    if(myFile){
        Serial.println("Opening test.");
        Serial.print("Position");
        Serial.println(myFile.position());
        while(myFile.available()){
            myFile.read(intContents, 100);
        }

        myFile.close();
    }
    
    for(int i = 0; i < 100; i++) {
        
        if(intContents[i] == NULL)
            break;

        Serial.println(intContents[i]);
    }

    return false; 

}

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");

    Wire.begin();
    SPI.begin();

    if (!myColor.begin()) {
        Serial.println("OPT4048 not detected. Please check wiring. Freezing...");
        while (1) ;
    }
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        while (1);
    }

    Serial.print("Initializing SD card...");
    Serial.println("Card initialized.");

    ledChip.Begin();
    ledChip.Enable();
    ledChip.SetChargePumpMode(CP_BYPASS);

    delay(100);

    for(uint8_t i = 0; i < 9; i++) {
        ledChip.SetLogBrightness(i, true);
    }

    testSD();
    while(1);

    ledChip.SetChannelPWM(channel[ROYAL_BLUE]-1, 50);
    // Color sensor setup
    myColor.setRange(RANGE_2KLUX2);
    //Serial.println(myColor.getRange());
    myColor.setConversionTime(CONVERSION_TIME_800MS);
    //Serial.println(myColor.getConversionTime());
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);

    lastTime = millis();

    myFile = SD.open("test.txt", FILE_WRITE); // Open file "data.txt"

    if(myFile){
        myFile.seek(0);
        Serial.println("File created.");
    }

    Serial.println("Great!");

}


void loop()
{
    myFile.write("Color, CIEx, CIEy, sample\n");

    if(myFile) {

        Serial.println("Measurements started.");
        for(int color = 0; color < FAR_RED; color++) {

            ledChip.SetChannelPWM(channel[color]-1, 50);

            // Color
            Serial.print("Color, ");
            Serial.println(color);
            myFile.print(color);
            myFile.print(", ");

            for(int sample = 0; sample < 3; sample++) {
                delay(3200);
                //myFile.print("\nCIEx: ");
                myFile.print(myColor.getCIEx()); 
                myFile.print(", ");
                //myFile.print("CIEy: "); 
                myFile.print(myColor.getCIEy());
                myFile.print(", ");
                //myFile.print("Sample:"); 
                myFile.print(sample+1);
                myFile.print("\n");
            }

            ledChip.SetChannelPWM(channel[color]-1, 0);

        }
    }

    if (millis() - lastTime > 30000)
        while(1);
}
