// AUTHOR: GUILLERMO PEREZ GUILLEN


#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire); 

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  sensors.begin();   
}

void loop() {
  sensors.requestTemperatures();   //The command to read the temperature is sent
  float temp= sensors.getTempCByIndex(0); //The temperature is obtained in ºC 
  Serial.print("Sending packet: ");
  Serial.println(counter);
  // send packet
  LoRa.beginPacket();
  LoRa.print(counter);
  LoRa.print(".- Temp = ");
  LoRa.print(temp);
  LoRa.print(" C");
  LoRa.endPacket();
  counter++;
  delay(4000);
}
