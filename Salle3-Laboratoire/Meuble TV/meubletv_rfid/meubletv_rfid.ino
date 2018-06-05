
/*
Meuble TV detection de la carte rfid

cablage RFID:
SDA --> 9
SCK --> 13
MOSI --> 11
MISO --> 12
GND --> GND
RST --> 8
3.3V --> 3.3V

 */

#include <SPI.h>
#include <RFID.h>
#include <Wire.h>

// variables pour lecture RFID
RFID RFID(9,8);
int UID[5]={};
int MASTERKEY[5]={54,25,238,6,199}; // UID du badge ou de la carte acceptée sous forme de tableau (Array).
bool statut = 1;

char rfidState ='N';

void setup() {

  // WIRE
  Wire.begin(4);
  Wire.onRequest(requestEvent);

  // RFID
  SPI.begin();
  RFID.init();
  
  // start serial port:
  Serial.begin(9600);
  
}

void loop() { 
   
    testRFID();
  // Serial.println("gogo");
  
  
}

void requestEvent()
{
  // il faut retourner l'etat de la detection RFID ( 'Y' ou 'N')
  Serial.print("etat RFID envoye dans i2C:");
  Serial.println(rfidState);
  Wire.write(rfidState);

}

boolean testRFID(){

  if (RFID.isCard()) {  
        // la carte est présente, on set la variable rfidState = 'Y';
          rfidState = 'Y';
          Serial.println("rfid detecte");
           RFID.halt();
          }
   else {
        // la carte est absente, on set la variable rfidState = 'N';
          rfidState = 'N';
           RFID.halt();
    }        
             
        //  RFID.halt();
       
  }



