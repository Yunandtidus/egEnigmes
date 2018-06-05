/*
Festion du bouton bureau dans la salle
un appui sur un bouton envoi une requete au back pour changer la source des cameras

 */

#include <SPI.h>
#include <Ethernet.h>
#include <Bounce2.h>
#define NUM_BUTTONS 1
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2};
Bounce * buttons = new Bounce[NUM_BUTTONS];



// variables ethernet
String inputString = "";
boolean stringComplete = false;
boolean test = false;
int compteur = 0;

// variable en retour ethernet
String codeRetour = "";

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xAB, 0xAD, 0xCD, 0xEF, 0xAB, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168,1,83);


// initialize the library instance:
EthernetClient client;

//char server[] = "www.arduino.cc";
IPAddress server(192,168,1,70);

boolean etatbouton = false; 
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW; 
void setup() {
  
  Serial.begin(9600);
  Serial.print("gogo");

   for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    buttons[i].interval(25);              // interval in ms
  }


  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  
   bool needToToggleLed = false;


  for (int i = 0; i < NUM_BUTTONS; i++)  {
    // Update the Bounce instance :
    buttons[i].update();
    // If it fell, flag the need to toggle the LED
    if ( buttons[i].fell() ) {
      sethttpRequest();
      needToToggleLed = true;
    }
  }

  // if a LED toggle has been flagged :
  if ( needToToggleLed ) {
    // Toggle LED state :
    // envoi quelquechose au back
    if(compteur < 2){
       compteur = compteur +1;
    }
    else { 
      compteur = 0;
    }
   
  }
   
}

// this method makes a HTTP connection to the server:
void sethttpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
  
  Serial.println(compteur);

  // if there's a successful connection:
  if (client.connect(server, 1880)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /set?code=TV.CAMERA.NUMBER&value="+String(compteur)+" HTTP/1.1");
    client.println("Host: 192.168.1.76");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    //lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}







  
  

  
   



    
  


    
