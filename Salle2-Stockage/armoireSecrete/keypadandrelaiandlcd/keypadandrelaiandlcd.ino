#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27,16,2);

int groundpin = 10; // write 0 to get ground

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

void setup(){
 
  lcd.init();   
  Serial.begin(9600);
 lcd.backlight();
// lcd.setBacklight(0);
 
  lcd.print("code _");
 
  Serial.begin(9600);
  pinMode (relay, OUTPUT);
  digitalWrite (relay, HIGH);
}

void correctPIN() // do this if correct PIN entered
{
  digitalWrite (relay, LOW);
  Serial.println("bravo");
  lcd.clear();
  lcd.print("Bonjour Louis");
  delay(1000);
  digitalWrite (relay, HIGH);
  delay(5000);
  lcd.print("code _");
}
 
void incorrectPIN() // do this if incorrect PIN entered
{
  
  Serial.println("incorrect");
  for (int zz=0; zz<4; zz++)
  {
    attempt[zz]='0';
  }
  lcd.clear();
  lcd.print("erreur de code");
  delay(2000);
  lcd.clear();
  lcd.print("code _");
  
  
}
 
void checkPIN()
{  
  Serial.println("checkpin led bleue");
  
 
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
 
void loop()
{
  
  readKeypad();
}
