
#include <SoftwareSerial.h>



#define ARDUINO_RX 6//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 7//connect to RX of the module
#include <Bounce2.h>

#define NUM_BUTTONS 1
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {2};
Bounce * buttons = new Bounce[NUM_BUTTONS];



const int laser_1 = 8;
const int laser_2 = 9;
const int laser_3 = 10;
const int laser_4 = 11;
const int laser_5 = 12;

// relai porte
int relayPorte = A0;


// code à l'envers :) ici la bonne combinaison c'est 4,2,5,2,1,1
int code_secret[] = {4,3,1,2,4,3,5};
int tableau[] ={0,0,0,0,0,0,0};

SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);

static int8_t Send_buf[8] = {0} ;
int z = 0;

#define CMD_PLAY_W_INDEX 0X03
#define CMD_SET_VOLUME 0X06
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_STOP_PLAY 016
#define CMD_SINGLE_CYCLE 0X19
#define SINGLE_CYCLE_ON 0X00
#define SINGLE_CYCLE_OFF 0X01
#define CMD_PLAY_W_VOL 0X22

int laser_un,laser_deux,laser_trois,laser_quatre,laser_cinq;
 boolean laser= false;
 boolean detected = false;
 boolean detected2 = false;
 boolean detected3 = false;
 boolean detected4 = false;
  boolean detected5 = false;

void setup() 
{

 for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    buttons[i].interval(25);              // interval in ms
  }

   
   // initialize the hall effect sensor pin as an input:
  pinMode(laser_1, INPUT); 
  pinMode(laser_2, INPUT);
  pinMode(laser_3, INPUT);
  pinMode(laser_4, INPUT);
  pinMode(laser_5, INPUT); 
  pinMode (relayPorte, OUTPUT);
  digitalWrite (relayPorte, HIGH);
    
	mySerial.begin(9600);
  Serial.begin(19200);

	Serial.println("gogo");
 sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
 
}


void loop() 
{
     
  laser_un = digitalRead(laser_1);
  laser_deux = digitalRead(laser_2);
  laser_trois = digitalRead(laser_3);
  laser_quatre = digitalRead(laser_4);
  laser_cinq = digitalRead(laser_5);  
  
  bool needToToggleLed = false;


  for (int i = 0; i < NUM_BUTTONS; i++)  {
    // Update the Bounce instance :
    buttons[i].update();
    // If it fell, flag the need to toggle the LED
    if ( buttons[i].fell() ) {
      
      needToToggleLed = true;
    }
  }

  // if a LED toggle has been flagged :
  if ( needToToggleLed ) {
    // Toggle LED state :
    // envoi quelquechose au back
    Serial.println("bouton");
     sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class  
  }
   
     if(!laser_un && !detected){
        Serial.println("detecté laser un");  
//        delay(500);//Wait chip initialization is complete
 //       sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
//        delay(200);//wait for 200ms
        sendCommand(CMD_PLAY_W_VOL, 0X0F02);//play the first song with volume 15 class  
        detected = true;
        add_secret_entry(1);
      }
      else if(laser_un) {        
       // sendCommand(CMD_STOP_PLAY,0);//play the first song with volume 15 class    
        detected = false; 
        }     
          
     if(!laser_deux && !detected2){
        Serial.println("detecté laser deux");  
//        delay(500);//Wait chip initialization is complete
     //    sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
//        delay(200);//wait for 200ms
        sendCommand(CMD_PLAY_W_VOL, 0X0F03);//play the first song with volume 15 class  
        
        detected2 = true;
        add_secret_entry(2);
      }
      else if(laser_deux) {        
       // sendCommand(CMD_STOP_PLAY,0);//play the first song with volume 15 class    
        detected2 = false; 
        }
        
     if(!laser_trois && !detected3){
        Serial.println("detecté laser trois");  
//        delay(500);//Wait chip initialization is complete
    //     sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
//        delay(200);//wait for 200ms
        sendCommand(CMD_PLAY_W_VOL, 0X0F04);//play the first song with volume 15 class  
        detected3 = true;
        add_secret_entry(3);
      }
      else if(laser_trois) {        
       // sendCommand(CMD_STOP_PLAY,0);//play the first song with volume 15 class    
        detected3 = false; 
        }
      
     if(!laser_quatre && !detected4){
        Serial.println("detecté laser quatre");  
//        delay(500);//Wait chip initialization is complete
    //     sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
//        delay(200);//wait for 200ms
        sendCommand(CMD_PLAY_W_VOL, 0X0F05);//play the first song with volume 15 class  
        detected4 = true;
        add_secret_entry(4);
      } 
      else if(laser_quatre) {        
       // sendCommand(CMD_STOP_PLAY,0);//play the first song with volume 15 class    
        detected4 = false; 
        }
  
     if(!laser_cinq && !detected5){
        Serial.println("detecté laser cinq");  
//        delay(500);//Wait chip initialization is complete
  //       sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
//        delay(200);//wait for 200ms
        sendCommand(CMD_PLAY_W_VOL, 0X0F06);//play the first song with volume 15 class  
        detected5 = true;
        add_secret_entry(5);
      }
      else if(laser_cinq) {        
       // sendCommand(CMD_STOP_PLAY,0);//play the first song with volume 15 class 
          
        detected5 = false; 
        }
   
 
}

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]) ;
  }
}

void add_secret_entry(int entry){

    tableau[7] = tableau[6];  
    tableau[6] = tableau[5];
    tableau[5] = tableau[4];
    tableau[4] = tableau[3];
    tableau[3] = tableau[2];
    tableau[2] = tableau[1];
    tableau[1] = tableau[0];
    tableau[0] = entry;
    checkSecret();
  }

  void checkSecret(){

    for(int i=0;i<7;i++){
      Serial.println(tableau[i]);   
      if(tableau[i] == code_secret[i]){
        z++;
        }   
      
      }     

      if(z==7){
        delay(1000);
        
        for(int i=0;i<7;i++){
          tableau[i] = 0;
        }   
      
           z=0 ;
      
        Serial.println("gagné");
        digitalWrite (relayPorte, LOW);
        delay(1000);
        digitalWrite (relayPorte, HIGH);
        }
        else{
        z=0;  
          }
    }



