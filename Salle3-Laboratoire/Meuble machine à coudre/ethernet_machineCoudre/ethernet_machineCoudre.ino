/*
Meuble Machine a coudre
Des que le cylindre est en position (detection RFID) on change le statut du cylindre dans le back
le cylindre passe de etat 0 à etat 1

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
#include <Ethernet.h>
#include <RFID.h>

// variables pour lecture RFID
RFID RFID(9,8);
int UID[5]={};
int MASTERKEY[5]={54,25,238,6,199}; // UID du badge ou de la carte acceptée sous forme de tableau (Array).
bool statut = 1;

// variables ethernet
String inputString = "";
boolean stringComplete = false;
boolean test = false;

// variable en retour ethernet
String codeRetour = "";

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xAB, 0xAD, 0xBA, 0xEF, 0xFE, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168,1,75);

// fill in your Domain Name Server address here:
IPAddress myDns(1, 1, 1, 1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


// initialize the library instance:
EthernetClient client;

//char server[] = "www.arduino.cc";
IPAddress server(192,168,1,70);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup() {

   // disable SD card if used
 // pinMode(4,OUTPUT);
 // digitalWrite(4,HIGH);

  // disable RFID SPI
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);

 //pinMode(10,OUTPUT);
 //digitalWrite(10,HIGH); 

  // RFID
  SPI.begin();
  RFID.init();
  
  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
 
   if(codeRetour == "Coucou"){
    testRFID();
   
        //le code machine a coudre à été saisi, on active les led en bleu
        if (testRFID()){
          // RFID ok et carte presente
          // on passe les led en vert
          // on met à jour le status du cylindre (passe de 0 à 1)
          
          }
        
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
     stringComplete = true;
     
   }   
  }

 

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {    
   //  sethttpRequest();        
      httpRequest();     
     if (stringComplete) {       
       codeRetour = getParameter(inputString);
       Serial.println(codeRetour);       
     } 
  }
}

boolean testRFID(){

  if (RFID.isCard()) {  

          /* Lecture du tag */
          if (RFID.readCardSerial())           
          {        
          Serial.print("L'UID est: ");
            for(int i=0;i<=4;i++)
            {
              UID[i]=RFID.serNum[i];
              Serial.print(UID[i],DEC);
              Serial.print(".");
            }
            Serial.println("");
          }
          /* fin de  Lecture du tag */
          
          if (UID[0] == MASTERKEY[0]   // Si l'UID 0  est égale à 1
           && UID[1] == MASTERKEY[1]   // Et si l'UID 1  est égale à 171
           && UID[2] == MASTERKEY[2]   // Et si l'UID 2  est égale à 43
           && UID[3] == MASTERKEY[3]   // Et si l'UID 3  est égale à 97
           && UID[4] == MASTERKEY[4])  // Et si l'UID 4  est égale à 224
            {
              return true;
            }
            else
            {
              return false;
            }
            
          RFID.halt();
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
    client.println("Host: 192.168.1.70");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection marche pas");
  }
}

// this method makes a HTTP connection to the server:
void sethttpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /set?code=ADMIN.TO.USER&value=bipbip HTTP/1.1");
    client.println("Host: 192.168.1.75");
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
