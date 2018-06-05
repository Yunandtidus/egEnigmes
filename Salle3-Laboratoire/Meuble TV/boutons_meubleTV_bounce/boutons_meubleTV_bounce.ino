/*
Boutons du meuble TV
a chaque appui sur un bouton le code est envoyé vers le serveur

 */

// ethernet
#include <SPI.h>
#include <Wire.h>


#include <Bounce2.h>

#define LED_PIN 13

#define NUM_BUTTONS 10
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

int ledState = LOW;

Bounce * buttons = new Bounce[NUM_BUTTONS];



//tableau a envoyer au back
char tableau[] ={'0','0','0','0','0','0','0','0','0','0'};
char codesaisi[10];
String str="";


void setup() {
  
  Serial.begin(9600);
  Serial.println("gogo slave 2 - boutons");
  Wire.begin(2);
  Wire.onRequest(requestEvent);
  
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    buttons[i].interval(25);              // interval in ms
  }

  // Setup the LED :
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
 
 }

void loop() {
  
  
 bool needToToggleLed = false;


  for (int i = 0; i < NUM_BUTTONS; i++)  {
    // Update the Bounce instance :
    buttons[i].update();
    // If it fell, flag the need to toggle the LED
    if ( buttons[i].fell() ) {
     
      add_secret_entry(i);
      needToToggleLed = true;
    }
  }

  // if a LED toggle has been flagged :
  if ( needToToggleLed ) {
    // Toggle LED state :
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
   
}

void requestEvent()
{
  Serial.println("requestEvent");
  Wire.write(tableau);
}


void add_secret_entry(int entry){ 
  Serial.print("coucou: ");
   Serial.println(entry);
  tableau[9] = tableau[8];
  tableau[8] = tableau[7];
  tableau[7] = tableau[6];
  tableau[6] = tableau[5];
   tableau[5] = tableau[4];
    tableau[4] = tableau[3];
    tableau[3] = tableau[2];
    tableau[2] = tableau[1];
    tableau[1] = tableau[0];
    tableau[0] = entry +'0';
    Serial.print("tableau:");
    Serial.println(tableau);
    } 
    
    
  


    
