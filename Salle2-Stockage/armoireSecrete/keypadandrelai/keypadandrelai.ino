#include <Keypad.h>

int groundpin = 10; // write 0 to get ground
int bluepin = 11; // select the pin for the green LED
int greenpin = 12; // select the pin for the red LED
int redpin = 13; // select the pin for the blue LED

int relay = A0; // select the pin for the blue LED

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','#','#'},
  {'a','b','c','d'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const char PIN[4]={
  '1','2','a','b'}; // our secret (!) number
char attempt[4]={
  '0','0','0','0'}; // used for comparison
int z=0;

void setup(){
  Serial.begin(9600);
  pinMode (redpin, OUTPUT);
  pinMode (greenpin, OUTPUT);
  pinMode (bluepin, OUTPUT);
  pinMode (groundpin, OUTPUT);
  pinMode (relay, OUTPUT);
  digitalWrite (groundpin, LOW);
  digitalWrite (relay, HIGH);
}

void correctPIN() // do this if correct PIN entered
{
  analogWrite (redpin,0);
  analogWrite (bluepin,0);
  analogWrite (greenpin,255);
  digitalWrite (relay, LOW);
  Serial.println("bravo");
  delay(1000);
  digitalWrite (relay, HIGH);
}
 
void incorrectPIN() // do this if incorrect PIN entered
{
  analogWrite (redpin,255);
  analogWrite (bluepin,0);
  analogWrite (greenpin,0);
  
  Serial.println("incorrect");
  for (int zz=0; zz<4; zz++)
  {
    attempt[zz]='0';
  }
  delay(1000);
  
  
}
 
void checkPIN()
{  
  Serial.println("checkpin led bleue");
  
 
  analogWrite (bluepin,255);
  delay(1000);
  Serial.println("fin");
  int correct=0;
  int i;
  for ( i = 0;   i < 4 ;  i++ )
  {
 
    if (attempt[i]==PIN[i])
    {
      correct++;
    }
  }
  if (correct==4)
  {
    correctPIN();
    
  }
  else
  {
    incorrectPIN();
   
  }
 
  
}


 
void readKeypad()
{
  analogWrite (redpin,0);
  analogWrite (bluepin,0);
  analogWrite (greenpin,0);
  
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Serial.println(key);
    attempt[z]=key;   
    z++;
    switch(key)
    {
    case '*':
      z=0;
      break;
    case '#':
      z=0;
      delay(100); // for extra debounce
     default:
     if(z == 4){
       Serial.println("checkpin");
       z=0;
      checkPIN();
      break;
      }
      
    }
     
    
  }
}
 
void loop()
{
  
  readKeypad();
}
