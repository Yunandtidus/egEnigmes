/*
Boutons du meuble TV
a chaque appui sur un bouton le code est envoyé vers le serveur

 */

// ethernet
#include <SPI.h>
#include <Wire.h>



//boutons
const int buttonPin0 = 2;
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 6;
const int buttonPin5 = 7;
const int buttonPin6 = 8;
const int buttonPin7 = 9;
const int buttonPin8 = 10;
const int buttonPin9 = 11;

//tableau a envoyer au back
char tableau[] ={'0','0','0','0','0','0','0','0','0','0'};
char codesaisi[10];
String str="";

int buttonState0 = 0;         // current state of the button
int lastButtonState0 = 0;     // previous state of the button

int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button

int buttonState3 = 0;         // current state of the button
int lastButtonState3 = 0;     // previous state of the button

int buttonState4 = 0;         // current state of the button
int lastButtonState4 = 0;     // previous state of the button

int buttonState5 = 0;         // current state of the button
int lastButtonState5 = 0;     // previous state of the button

int buttonState6 = 0;         // current state of the button
int lastButtonState6 = 0;     // previous state of the button

int buttonState7 = 0;         // current state of the button
int lastButtonState7 = 0;     // previous state of the button

int buttonState8 = 0;         // current state of the button
int lastButtonState8 = 0;     // previous state of the button

int buttonState9 = 0;         // current state of the button
int lastButtonState9 = 0;     // previous state of the button



unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  Serial.begin(9600);
  Serial.println("gogo slave 2 - boutons");

  Wire.begin(2);
  Wire.onRequest(requestEvent);

 // start serial port:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  pinMode(buttonPin0, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);  
  
 
}

void loop() {
  
  // button 0
  int buttonState0 = digitalRead(buttonPin0);
  if (buttonState0 != lastButtonState0) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState0 != lastButtonState0) {
      lastButtonState0 = buttonState0;
      if (lastButtonState0 == HIGH) {
        add_secret_entry('0');
      }
    }
  }
  lastButtonState0 = buttonState0;
  
  // button 1
  int buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 != lastButtonState1) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState1 != lastButtonState1) {
      lastButtonState1 = buttonState1;
      if (lastButtonState1 == HIGH) {
        add_secret_entry('1');
      }
    }
  }
  lastButtonState1 = buttonState1;
  
  
  // button 2
 int buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 != lastButtonState2) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState2 != lastButtonState2) {
      lastButtonState2 = buttonState2;
      if (lastButtonState2 == HIGH) {
        add_secret_entry('2');
      }
    }
  }
  lastButtonState2 = buttonState2;

  // button 3
  
  int buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 != lastButtonState3) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState3 != lastButtonState3) {
      lastButtonState3 = buttonState3;
      if (lastButtonState3 == HIGH) {
        add_secret_entry('3');
      }
    }
  }
  lastButtonState3 = buttonState3;
  
  
  //button4
  
  int buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 != lastButtonState4) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState4 != lastButtonState4) {
      lastButtonState4 = buttonState4;
      if (lastButtonState4 == HIGH) {
        add_secret_entry('4');
      }
    }
  }
  lastButtonState4 = buttonState4;
  
  //button 5
  
  int buttonState5 = digitalRead(buttonPin5);
  if (buttonState5 != lastButtonState5) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState5 != lastButtonState5) {
      lastButtonState5 = buttonState5;
      if (lastButtonState5 == HIGH) {
        add_secret_entry('5');
      }
    }
  }
  lastButtonState5 = buttonState5;
  
  // button 6
  int buttonState6 = digitalRead(buttonPin6);
  if (buttonState6 != lastButtonState6) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState6 != lastButtonState6) {
      lastButtonState6 = buttonState6;
      if (lastButtonState6 == HIGH) {
        add_secret_entry('6');
      }
    }
  }
  lastButtonState6 = buttonState6;
  
  //button 7
  int buttonState7 = digitalRead(buttonPin7);
  if (buttonState7 != lastButtonState7) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState7 != lastButtonState7) {
      lastButtonState7 = buttonState7;
      if (lastButtonState7 == HIGH) {
        add_secret_entry('7');
      }
    }
  }
  lastButtonState7 = buttonState7;
  
  //button 8
  int buttonState8 = digitalRead(buttonPin8);
  if (buttonState8 != lastButtonState8) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState8 != lastButtonState8) {
      lastButtonState8 = buttonState8;
      if (lastButtonState8 == HIGH) {
        add_secret_entry('8');
      }
    }
  }
  lastButtonState8 = buttonState8;
  
  // button 9
  int buttonState9 = digitalRead(buttonPin9);
  if (buttonState9 != lastButtonState9) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState9 != lastButtonState9) {
      lastButtonState9 = buttonState9;
      if (lastButtonState9 == HIGH) {
        add_secret_entry('9');
      }
    }
  }
  lastButtonState9 = buttonState9;
  
  
   
}

void requestEvent()
{
  Serial.println("requestEvent");
  
  Wire.write(tableau);
 
}

void resetArray(){
  
  for (int j=0; j<9;j++){
    tableau[j]='0';
    }
  }

void add_secret_entry(char entry){ 
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
    tableau[0] = entry;
    
  } 

  



    
