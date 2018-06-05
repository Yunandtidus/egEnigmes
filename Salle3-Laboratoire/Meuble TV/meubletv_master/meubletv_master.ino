// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <Ethernet.h>


#define NODE_READ_DELAY 500 // Some delay between I2C node reads



// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xAB, 0xBD, 0xBE, 0xFF, 0xFE, 0xED
};

// variables ethernet
String inputString = "";
boolean stringComplete = false;
// variable en retour ethernet
String codeRetour = "";


// RFID 
char rfidAuthorization='N';
char lastrfidAuthorization = 'N';
// code boutons meuble tv
char arrayCodeboutons[10];
String codeBoutonsToBackend="";

// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192,168,1,82);
// fill in your Domain Name Server address here:
//IPAddress myDns(1, 1, 1, 1);
// initialize the library instance:
EthernetClient client;
//char server[] = "www.arduino.cc";
IPAddress server(192,168,1,70);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup()
{

  Serial.begin(9600); 
  // give the ethernet module time to boot up:
  Serial.print("Setup lancé, on attend 2mn avant de lancer la connexion");
  delay(120000);
  Ethernet.begin(mac, ip);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  // setup I2C
   
  Serial.println("MASTER READER NODE");
  Serial.println("***********************");
  
  Wire.begin();        // Activate I2C link
}

void loop()
{
// interrogation des composants en I2C (
// demande du code a l'arduino boutons 
// demande etat du capteur RFID 
// et envoi du code de lumière à l'arduino qui gere la lumière)
// slave 2 == boutons du meuble TV
// slave 3 == gestion de la lumière
// slave 4 == arduino RFID (lecteur de disquette)

// request RFID slave 4
  Wire.requestFrom(4, 1);    // request 1 bytes from slave device #4
  Serial.println("request slave 4 - Etat rfid ");
  while (Wire.available()) { // slave may send less than requested
    rfidAuthorization = Wire.read(); // receive a byte as character
    Serial.print("etat rfid :");        // print the character
    Serial.println(rfidAuthorization);        // print the character
    }
if(rfidAuthorization != lastrfidAuthorization){
  if(rfidAuthorization == 'Y'){
    // RFID detection is OK, send the result to the backend
    Serial.println("detection RFID ok, send data to backend");
    setRFIDhttpRequest();
  }
}
  lastrfidAuthorization = rfidAuthorization;
  
  if(rfidAuthorization == 'Y'){
    // requete I2C du code des boutons slave 2
    Wire.requestFrom(2, 10);    // request 1 bytes from slave device #2
    Serial.println("request slave 2 - code boutons");
    while (Wire.available()) { // slave may send less than requested
   
      for (int i = 0; i < 10; i++) arrayCodeboutons[i] = Wire.read(); 
     // for (int j = 0; j < 10; j++) Serial.println(arrayCodeboutons[j]);   // print nodes data 
             // print the character
      }
      // retour du slave terminé on envoi l'état des boutons
      sethttpBioRequest();
      sethttpCoudreRequest();
  }
  
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) { 
      // on demande au back la lumière de la salle à interval régulier    
      httpRequest();
  }
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {    
    char inChar = client.read();        
    inputString += inChar;
   // if the incoming character is a newline, set a flag
   // so the main loop can do something about it:
    if (inChar == '\n') {
      codeRetour = getParameter(inputString);
      Serial.print("code retour de la lumière: ");
      Serial.println(codeRetour); 
   }   
  }

  
}

// Envoi du code des boutons
void sethttpBioRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  codeBoutonsToBackend = String(arrayCodeboutons);
  Serial.print("code des boutons envoyés: ");
  Serial.println(codeBoutonsToBackend);
  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /set?code=COMPUTER2.VARIABLE.CODE&value="+codeBoutonsToBackend+" HTTP/1.1");
    client.println("Host: 192.168.1.82");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

// Envoi du code des boutons
void sethttpCoudreRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  codeBoutonsToBackend = String(arrayCodeboutons);
  Serial.print("code des boutons envoyés: ");
  Serial.println(codeBoutonsToBackend);
  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /set?code=COMPUTER1.VARIABLE.CODE&value="+codeBoutonsToBackend+" HTTP/1.1");
    client.println("Host: 192.168.1.82");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

// Send RFID state to backend
void setRFIDhttpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /set?code=MEUBLETV.VARIABLE.RFID&value=Y HTTP/1.1");
    client.println("Host: 192.168.1.82");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting..test");
    // send the HTTP GET request:
   // client.println("GET /getAll HTTP/1.1");
    client.println("GET /getText?code=COMPUTER1.VARIABLE.CODE HTTP/1.1");
    client.println("Host: 192.168.1.82");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

String getParameter(String response){  //ne recupere que la variable dans la reponse
  
  int lengthOfString = inputString.length();     
    int endHttpHeader = inputString.indexOf("\r\n\r\n");    
    String variable = inputString.substring(endHttpHeader,lengthOfString);
    variable.trim();   
    inputString = "";
    return variable;
  }
