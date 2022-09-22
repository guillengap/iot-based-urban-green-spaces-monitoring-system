// AUTHOR: GUILLERMO PEREZ GUILLEN

#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h> // DS1B20->               
#include <DallasTemperature.h>
#include <Wire.h> // LCD->
#include "rgb_lcd.h"
rgb_lcd lcd;
const int colorR = 173;
const int colorG = 255;
const int colorB = 47;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire); 

int counter = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  // Print a message to the LCD.
  lcd.print("ECOLOGY!");  
  lcd.setCursor(0, 1); // LCD 
  lcd.print("LoRa Sender");
  if (!LoRa.begin(915E6)) {
  lcd.setCursor(0, 1); // LCD 
  lcd.print("Starting LoRa failed!");    
    while (1);
  }
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();   //The command to read the temperature is sent
  int temp= sensors.getTempCByIndex(0); //The temperature is obtained in ºC
  lcd.clear();
  lcd.setCursor(0, 0); // LCD 
  lcd.print("Packet:");    
  lcd.setCursor(8, 0); // LCD 
  lcd.print(counter);
  lcd.setCursor(0, 1); // LCD 
  lcd.print("Temp:");    
  lcd.setCursor(8, 1); // LCD 
  lcd.print(temp);
  // send packet
  LoRa.beginPacket();
  LoRa.print(temp);
  LoRa.endPacket();
  counter++;
  delay(4000);
}
