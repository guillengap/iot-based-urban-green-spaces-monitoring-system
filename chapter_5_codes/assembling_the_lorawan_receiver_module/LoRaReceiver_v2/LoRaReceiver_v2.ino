// AUTHOR: GUILLERMO PEREZ GUILLEN

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

char cadena[30]; //We create an array that will store the characters that we will write in the PC console. We assign a limit of characters, in this case 30
byte posicion=0;  //Variable to change the position of the characters in the array
int valor;  //Integer Variable

void setup() {  
  lcd.init();  // Initiate the LCD:
  lcd.backlight();  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    memset(cadena, 0,sizeof(cadena));//memset deletes the contents of the array "cadena" from position 0 to the end sizeof
    // received a packet
    Serial.print("Received packet... ");    
    // read packet
    while (LoRa.available()) {      
      char dedos= (char)LoRa.read();
      Serial.print(dedos);
      cadena[posicion]=dedos;//Read a character from the string "cadena" from "posicion", then read the next character with "posicion++"
      posicion++;
    }
    valor=atoi(cadena);//Convert the string to integers
    Serial.println();
    Serial.print(" temp=");
    Serial.print(valor);
    posicion=0;
    // print RSSI of packet
    int dedal = LoRa.packetRssi();
    Serial.print(" with RSSI: ");
    Serial.println(dedal);
    lcd.clear();
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("Temp:"); 
    lcd.setCursor(6, 0); 
    lcd.print(valor);
    lcd.setCursor(0, 2); // Set the cursor on the first column and second row.
    lcd.print("RSSI:"); 
    lcd.setCursor(5, 2); //Set the cursor on the fifth column and the second row (counting starts at 0!).
    lcd.print(dedal);        
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW); 
  }
}
