#include <RFID.h>
#include <SPI.h>


RFID RFID(10,9);

int UID[5];

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  RFID.init();  
  Serial.println("bipbip");

}

void loop()
{
    if (RFID.isCard()) {  
         Serial.println("rfid");
          }          
        
   
    delay(100);    
}
