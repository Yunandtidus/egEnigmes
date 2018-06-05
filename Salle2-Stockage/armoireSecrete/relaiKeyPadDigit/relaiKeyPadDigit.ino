/*
  Project: 4-Digit 7-segment display module (common cathode)
  Function: Timer. You can see the number on timer decreases by 1 second from 20 to 0 then timer will flash twice and restart
  in 2 seconds
*/

#include <Keypad.h>
#include <Wire.h
// setup keypad

int relay = A0; // select the pin for the blue LED

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7','A','B','1'},
  {'6','8','2','F'},
  {'5','3','9','E'},
  {'4','C','D','0'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const char PIN[4]={
  '4','A','8','2'}; // our secret (!) number
char attempt[4]={
  '0','0','0','0'}; // used for comparison
int z=0;



//*************************************************************
//the pins of 4-digit 7-segment display attached to arduino board digital pins 2 - 13 respectively
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int DP = 9;// dot is not used in this project
const int D1 = 10;
const int D2 = 11;
const int D3 = 12;
const int D4 = 13;

int dig1 = 0;
int dig2 = 0;
int dig3 = 2;
int dig4 = 0;

//*************************************************************
void setup()
{
  Serial.begin(9600);//initialize serial communications at 9600 bps
//set all the pins of the LED display as output

  //set relai
  pinMode (relay, OUTPUT);
  digitalWrite (relay, HIGH);

  //set afficheur 7 segments
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(DP, OUTPUT);
}

void loop()
{
    readKeypad(); 
} 
//*************************************************************
//The function is to control the 7-segment LED display to display numbers. Here x is the number to be displayed. It is an integer from 0 to 9 

void pickLetters(string x) {
  
}
//*************************************************************
void clearLEDs()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(DP, LOW);
}

void letterA()             //Lettre A
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH););
}

void letterB()             //Lettre B
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH););
}

void number1()             //Number 1
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number2()             //Number 2
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void number3()            //Number 3
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void number4()             //Number 4
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number5()             //Number 5
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number6()             //Number 6
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number7()            //Number 7
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void number8()            //Number 8
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number9()             //Number 9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void number0()             //Number 0
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void correctPIN() // do this if correct PIN entered
{
  digitalWrite (relay, LOW);
  Serial.println("bravo");
  delay(1000);
  digitalWrite (relay, HIGH);
  delay(5000);  
}
 
void incorrectPIN() // do this if incorrect PIN entered
{
  
  Serial.println("incorrect");
  for (int zz=0; zz<4; zz++)
  {
    attempt[zz]='0';
  }
  
  delay(1000);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        delay(500);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
        delay(500);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        delay(500);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);  
}
 
void checkPIN()
{  
  Serial.println("checkpin");   
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

// exemple d'affichage
    digitalWrite(D4, LOW);    //Digit 4
    pickLetters(dig4);   
    digitalWrite(D4, HIGH);

    digitalWrite(D3, LOW);    //Digit 3
    pickLetters(dig3);    
    digitalWrite(D3, HIGH);

    digitalWrite(D2, LOW);   //Digit 2
    pickLetters(dig2);    
    digitalWrite(D2, HIGH);

    digitalWrite(D1, LOW);   //Digit 1
    pickLetters(dig1);
    delay(delayTime);
    digitalWrite(D1, HIGH);
    

  
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Serial.println(key);
    attempt[z]=key;   
    
    if(z == 0 ){
      lcd.clear();
      }
      lcd.write(key);
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
