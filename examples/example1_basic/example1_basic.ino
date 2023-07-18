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
#define ARRAY_SIZE 20   

SparkFun_OPT4048 blackMask;
SparkFun_OPT4048 redMask;
Lp55231 ledChip(LED_ADDRESS);

const int channel[] = {2,1,7,3,4,8,5,6,9};
const int chipSelect = 5;
char intContents[ARRAY_SIZE] = {};

unsigned long lastTime;
File myFile; 

void testSD()
{
    
    myFile = SD.open("test.txt", FILE_WRITE);

    if(!myFile){
        Serial.println("Could not read, or create file.");
        while(1);
    }

    if(myFile) {

        myFile.println(21);
        myFile.close(); 
    }

    delay(100);

    myFile = SD.open("test.txt", FILE_READ);

    if(myFile){
        Serial.println("Opening test.");
        Serial.print("Position: ");
        Serial.println(myFile.position());
        while(myFile.available()){
            myFile.read(intContents, ARRAY_SIZE);
        }

        myFile.close();
    }
    
    for(int i = 0; i < ARRAY_SIZE; i++) {
        
        if(intContents[i] == NULL)
            break;

        Serial.println(intContents[i]);
    }
    
    Serial.println("Success.");
    while(1);

}

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");

    Wire.begin();
    SPI.begin();

    if (!blackMask.begin() || !redMask.begin(OPT4048_ADDR_HIGH)) {
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

    for(int i = 0; i < 9; i++) {
        ledChip.SetLogBrightness(i, true);
    }

    //testSD();

    //ledChip.SetChannelPWM(channel[ROYAL_BLUE]-1, 50);
    // Color sensor setup
    blackMask.setRange(RANGE_2KLUX2);
    redMask.setRange(RANGE_2KLUX2);
    //Serial.println(blackMask.getRange());
    blackMask.setConversionTime(CONVERSION_TIME_800MS);
    redMask.setConversionTime(CONVERSION_TIME_800MS);
    //Serial.println(blackMask.getConversionTime());
    blackMask.setOperationMode(OPERATION_MODE_CONTINUOUS);
    redMask.setOperationMode(OPERATION_MODE_CONTINUOUS);

    lastTime = millis();

    myFile = SD.open("colorData.txt", FILE_WRITE); // Open file "data.txt"

    if(myFile){

        myFile.seek(0);
        Serial.println("File created.");
        delay(100);
        myFile.println("Red/Black, Color, CIEx, CIEy, sample");
        myFile.close();

    }

    Serial.println("Great!");

    while(!(Serial.available() > 0)){
        delay(10);
    }



}


void loop()
{


    myFile = SD.open("colorData.txt", FILE_WRITE); // Open file "data.txt"

    // Total cycle of time 9 colors @ 9.6 seconds/3 samples == 86.4 seconds 
    if(myFile) {

        Serial.println("Measurements started.");
        for(int color = 0; color <= FAR_RED; color++) {

            ledChip.SetChannelPWM(channel[color]-1, 50);

            // Color
            Serial.print("Color, ");
            Serial.println(color);

            for(int sample = 0; sample < 3; sample++) {
                delay(3200);

                // Black Solder Mask
                myFile.print("b");
                myFile.print(", ");
                myFile.print(color);
                myFile.print(", ");
                myFile.print(blackMask.getCIEx()); 
                myFile.print(", ");
                myFile.print(blackMask.getCIEy());
                myFile.print(", ");
                myFile.println(sample+1);

                // Red Solder Mask
                myFile.print("r");
                myFile.print(", ");
                myFile.print(color);
                myFile.print(", ");
                myFile.print(redMask.getCIEx());
                myFile.print(", ");
                myFile.print(redMask.getCIEy());
                myFile.print(", ");
                myFile.println(sample+1);
            }

            ledChip.SetChannelPWM(channel[color]-1, 0);

        }
    }

    myFile.close();
    Serial.print("Time running: ");
    Serial.println(((millis() - lastTime)/1000)/60);

    if (millis() - lastTime > 864000){
        Serial.println("---------------------------------------------------");
        Serial.println("Finished");
        Serial.println("---------------------------------------------------");
        while(1);
    }
}
