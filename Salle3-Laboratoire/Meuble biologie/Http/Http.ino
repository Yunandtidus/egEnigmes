#include <SPI.h>
#include <RFID.h>

#include "Http.h"

/* -------------- WIRES ------------------
*
*        RFID              Arduino
*   +------------+    +---------------+
*   |         SDA|----|9            A0|----+ Green Leds
*   |         SCK|----|13           A1|----+ Red Leds
*   |        MOSI|----|11           A2|----+ Relai Boite
*   |        MISO|----|12           A3|----+ Relai Neon
*   |         GND|----|GND            |
*   |         RST|----|8           GND|----- Ground Relais
*   |        3.3V|----|3.3V        GND|----- Ground Leds
*   +------------+    +---------------+
*/

// Network configuration
const byte mac[] = { 0xAB, 0xAD, 0xCD, 0xEF, 0xFE, 0xED };
const IPAddress myIp(192,168,1,76);
const IPAddress server(192,168,1,70);

EthernetClient client;

// RFID
RFID RFID(10,9);

// PIN
const int pinRelaiGreenLed = A0;
const int pinRelaiRedLed = A1;
const int pinRelaiBoite = A2;
const int pinRelaiNeon = A3;

// httpClients
Http httpBio(false); //asynchronous
Http httpCoudre(false); //asynchronous
Http httpReservoir;

boolean biologieActivated = false;
boolean machineACoudreActivated = false;

boolean reservoirLoaded = false;

long rfidTimestamp = 0;
boolean rfidPresent = false;

void setup() {
  Serial.begin(9600);
  delay(1000); // to boot Ethernet module
  
  RFID.init();  
  Ethernet.begin(mac, myIp);
  
  Serial.println("Connecté au réseau, IP = " + Ethernet.localIP());
  
  // Init PINS
  pinMode (pinRelaiBoite, OUTPUT);
  digitalWrite (pinRelaiBoite, HIGH);
  
  pinMode (pinRelaiNeon, OUTPUT);
  digitalWrite (pinRelaiNeon, HIGH);
  
  pinMode (pinRelaiGreenLed, OUTPUT);
  digitalWrite (pinRelaiGreenLed, LOW);
  
  pinMode (pinRelaiRedLed, OUTPUT);
  digitalWrite (pinRelaiRedLed, LOW);
}

void loop(){
  // Get states from server and RFID 
  getStates();
  
  if (machineACoudreActivated && biologieActivated){
    
    digitalWrite (pinRelaiBoite, LOW);
    
    if (rfidTimestamp == 0){
      // Red LEDs
      digitalWrite (pinRelaiGreenLed, LOW);
      digitalWrite (pinRelaiRedLed, HIGH);
    } else if (millis() - rfidTimestamp < 3000){
      // clignote Red & Green
      digitalWrite (pinRelaiGreenLed, HIGH);
      digitalWrite (pinRelaiRedLed, HIGH);
      delay(200);
      digitalWrite (pinRelaiGreenLed, LOW);
      digitalWrite (pinRelaiRedLed, LOW);
      delay(200);
      return;
    } else {
      reservoirLoaded = true;
      // set var
      httpReservoir.request(server, 1880, "/set?code=RECEPTACLE.VIDEO&value=Y");
      // Green LEDs
      digitalWrite (pinRelaiGreenLed, HIGH);
      digitalWrite (pinRelaiRedLed, LOW);
    }
  } else {
    reservoirLoaded = false;
    // switch off LEDS
    digitalWrite (pinRelaiGreenLed, LOW);
    digitalWrite (pinRelaiRedLed, LOW);
    digitalWrite (pinRelaiBoite, LOW);
  }
  
  if (!biologieActivated){
    digitalWrite (pinRelaiNeon, LOW);
  } else {
    digitalWrite (pinRelaiNeon, HIGH);
  }
  
  delay(200);
}

void getStates(){
  String varBio = httpBio.request(server, 1880, "/getText?code=COMPUTER1.STEP");
  if (varBio == "Y"){
    biologieActivated = true;
  } else if (varBio == "N"){
    biologieActivated = false;
  }
  
  String varCoudre = httpCoudre.request(server, 1880, "/getText?code=COMPUTER2.STEP");
  if (varCoudre == "Y"){
    machineACoudreActivated = true;
  } else if (varCoudre == "N"){
    machineACoudreActivated = false;
  }
  
  if (RFID.isCard()) {
    if (!rfidPresent){
      Serial.println("RFID detected");
      rfidTimestamp = millis();
    }
    rfidPresent = true;
  } else {
    rfidTimestamp = 0;
    rfidPresent = false;
  }    
}
