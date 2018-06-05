/*
Meuble BIO

Des que le code du meuble bio est ok (COMPUTER2.CODE.VALUE = Y) on allume la lumière
Des que les deux codes des meubles bio et coudre sont ok 
(COMPUTER2.CODE.VALUE = Y)
(COMPUTER1.CODE.VALUE = Y)
il faut ouvrir la trappe dans le meuble bio
Des que le capteur RFID recoit une information (Leture directe) on met à jour le statut du cylindre
CYLINDRE.VARIABLE.CODE = 1
Tant que le meuble bio n'est pas activé, les leds sont éteintes
(COMPUTER2.CODE.VALUE = N)
Des que le meuble bio est activé les led sont allumées en rouge
(COMPUTER2.CODE.VALUE = Y)
Des que le capteur RFID est activé les leds sont allumées en vert
(Lecture directe)


Cablage que d'un seul relai

 */

#include <SPI.h>
#include <Ethernet.h>


// relai boite
int relayBoite = A0;

// relai lumiere
int relayLumiere = A1;

// variables ethernet
String inputString = "";
boolean test = false;

// variable en retour ethernet
String codeRetourBio = "";
String codeRetourCoudre = "";

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xAB, 0xAD, 0xCD, 0xEF, 0xFE, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168,1,76);
// fill in your Domain Name Server address here:
// initialize the library instance:
EthernetClient clientBio;
EthernetClient clientCoudre;
//char server[] = "www.arduino.cc";
IPAddress server(192,168,1,70);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup() {

  pinMode (relayBoite, OUTPUT);
  digitalWrite (relayBoite, HIGH);
  
  pinMode (relayLumiere, OUTPUT);
  digitalWrite (relayLumiere, HIGH);
 
 

  // start serial port:
  Serial.begin(9600);
  Serial.print("setup lancé attente de 2mn le temps de lancer le serveur");

  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {

  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {  
    httpRequestBio();
    httpRequestCoudre();
  }
  
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (clientBio.available()) {    
    char inChar = clientBio.read();        
   inputString += inChar;
   // if the incoming character is a newline, set a flag
   // so the main loop can do something about it:
   if (inChar == '\n') {
      codeRetourBio = getParameter(inputString);
      Serial.print("code bio");
      Serial.println(codeRetourBio); 
   }   
  }
  
  while (clientCoudre.available()) {    
    char inChar = clientCoudre.read();        
   inputString += inChar;
   // if the incoming character is a newline, set a flag
   // so the main loop can do something about it:
   if (inChar == '\n') {
      codeRetourCoudre = getParameter(inputString);
      Serial.print("code coudre");
      Serial.println(codeRetourCoudre); 
   }   
  }
  
  if(codeRetourBio == "Y" && codeRetourCoudre == "Y"){
    // on active le relai
    delay(1000);
        Serial.println("gagné");
        digitalWrite (relayBoite, LOW);
        delay(1000);
        digitalWrite (relayBoite, HIGH);
        codeRetourBio = "";
        codeRetourCoudre = "";
        }
}

String getParameter(String response){  //ne recupere que la variable dans la reponse
  Serial.println(response);
  int lengthOfString = inputString.length();     
    int endHttpHeader = inputString.indexOf("\r\n\r\n");    
    String variable = inputString.substring(endHttpHeader,lengthOfString);
    variable.trim();   
    inputString = "";
    return variable;
  }

// this method makes a HTTP connection to the server:
void httpRequestBio(){
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  clientBio.stop();

  // if there's a successful connection:
  if (clientBio.connect(server, 1880)) {
   // Serial.println("connecting to backend bio");
    // send the HTTP GET request:
   // client.println("GET /getAll HTTP/1.1");
    clientBio.println("GET /getText?code=COMPUTER1.STEP HTTP/1.1");
    clientBio.println("Host: 192.168.1.70");
    clientBio.println("User-Agent: arduino-ethernet");
    clientBio.println("Connection: close");
    clientBio.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection bio marche pas");
  }
}

void httpRequestCoudre(){
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  clientCoudre.stop();

  // if there's a successful connection:
  if (clientCoudre.connect(server, 1880)) {
   // Serial.println("connecting to backend coudre");
    // send the HTTP GET request:
   // client.println("GET /getAll HTTP/1.1");
    clientCoudre.println("GET /getText?code=COMPUTER2.STEP HTTP/1.1");
    clientCoudre.println("Host: 192.168.1.70");
    clientCoudre.println("User-Agent: arduino-ethernet");
    clientCoudre.println("Connection: close");
    clientCoudre.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection coudre marche pas");
  }
}
