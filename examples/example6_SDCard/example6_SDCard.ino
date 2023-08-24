/*
Example 6 - SD Card

This is a highly specialized example that uses the SparkX Visible Spectrum Emitter and this Color Sensor, to check
the relative accuracy of the color sensing capabilities of the Color Sensor. All of the LEDs on the Visible Spectrum 
Emitter are turned on for one conversion cycle, values are recorded in a comma-seperated list for easy integration 
into a spreadsheet, and then the next light is turned on. 

Color data is filed comma-separated as follows:
"Color tag, CIEx, CIEy, Sample number"

Written by Elias Santistevan @ SparkFun Electronics, July 2023

Products:
    Qwiic 1x1: https://www.sparkfun.com/products/22638
    Qwiic Mini: https://www.sparkfun.com/products/22639

Repository:
    https://github.com/sparkfun/SparkFun_OPT4048_Arduino_Library

SparkX Visible Spectrum Emitter used in this example:
* https://www.sparkfun.com/products/21316

SparkFun code, firmware, and software is released under the MIT 
License	(http://opensource.org/licenses/MIT).

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

SparkFun_OPT4048 myColor;
Lp55231 ledChip(LED_ADDRESS);

const int channel[] = {2,1,7,3,4,8,5,6,9};
const int chipSelect = 5;
char intContents[ARRAY_SIZE] = {};

unsigned long lastTime;
File myFile; 

/*
    If you're having trouble with the SD Card, then you can use the 
    following "testSD" function to test that it works. I found a few 
    failed SD cards this way. This funciton will open a file on the SD 
    Card, write a value, and then read it back. 
*/
void testSD()
{
    
    myFile = SD.open("test.txt", FILE_WRITE);

    if(!myFile)
    {
        Serial.println("Could not read, or create file.");
        while(1);
    }

    delay(100);

    myFile = SD.open("test.txt", FILE_READ);

    if(myFile)
    {
        Serial.println("Opening test.");
        Serial.print("Position: ");
        Serial.println(myFile.position());
        while(myFile.available()){
            myFile.read(intContents, ARRAY_SIZE);
        }

        myFile.close();
    }
    
    for(int i = 0; i < ARRAY_SIZE; i++) 
    {
        
        if(intContents[i] == NULL)
            break;

        Serial.println(intContents[i]);
    }
    
    Serial.println("Done.");
    while(1);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("OPT4048 Example 1 Basic");

    // Usng SPI for the SD Card.
    Wire.begin();
    SPI.begin();

    if (!myColor.begin()) 
    {
        Serial.println("OPT4048 not detected. Please check wiring. Freezing...");
        while (1) 
            ;
    }

    if (!SD.begin(chipSelect)) 
    {
        Serial.println("Card failed, or not present");
        while (1)
            ;
    }

    ledChip.Begin();
    ledChip.Enable();
    ledChip.SetChargePumpMode(CP_BYPASS);

    delay(100);

    for(int i = 0; i < 9; i++) 
        ledChip.SetLogBrightness(i, true);

    myColor.setRange(RANGE_2KLUX2);
    myColor.setConversionTime(CONVERSION_TIME_800MS);
    myColor.setOperationMode(OPERATION_MODE_CONTINUOUS);

    lastTime = millis();

    myFile = SD.open("colorData.txt", FILE_WRITE); 

    if(myFile)
    {
        myFile.seek(0);
        Serial.println("File created.");
        delay(100);
        myFile.println("Red/Black, Color, CIEx, CIEy, sample");
        myFile.close();
    }

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


    myFile = SD.open("colorData.txt", FILE_WRITE); // Open file "colorData.txt"

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
                myFile.print(myColor.getCIEx()); 
                myFile.print(", ");
                myFile.print(myColor.getCIEy());
                myFile.print(", ");
                myFile.println(sample+1);

            }

            ledChip.SetChannelPWM(channel[color]-1, 0);

        }
    }

    myFile.close();
    Serial.print("Time running: ");
    Serial.println(((millis() - lastTime)/1000)/60);

    // 9600 conversion time * 9 Colors
    if (millis() - lastTime > (9600 * 9){
        Serial.println("---------------------------------------------------");
        Serial.println("Finished");
        Serial.println("---------------------------------------------------");
        while(1);
    }
}
