#include "Nextion.h"
#include <Adafruit_MotorShield.h>

//Nextion
#define RXD2 18
#define TXD2 19
Nextion *next = Nextion::GetInstance(Serial1); // software serial

//Motoren Shields
Adafruit_MotorShield AFMSbot ( 0x61 ); // Adresse einlesen 
Adafruit_MotorShield AFMStop ( 0x60 );  

// Motorenadresse zuordnen
Adafruit_StepperMotor *myMotor1 = AFMSbot.getStepper(200, 1); 
Adafruit_StepperMotor *myMotor2 = AFMSbot.getStepper(200, 2);
Adafruit_StepperMotor *myMotor3 = AFMStop.getStepper( 200 , 1 );
Adafruit_StepperMotor *myMotor4 = AFMStop.getStepper( 200 , 2 );

// Button aus dem Display einlesen    next = instanz, 0 = Seiten ID, 0 = Element ID, b0 = Element Name
NexButton initButton1( next, 3, 2, "b0");  // Button 1-4 == Produkt kaufen 
NexButton initButton2( next, 4, 2, "b0"); 
NexButton initButton3( next, 5, 2, "b0");  
NexButton initButton4( next, 6, 2, "b0");  
NexButton initButton5( next, 3, 3, "b1");  // Button 5-8 == Seite verlassen
NexButton initButton6( next, 4, 3, "b1");  
NexButton initButton7( next, 5, 3, "b1");  
NexButton initButton8( next, 6, 3, "b1");
NexButton initButton9( next, 1, 12, "b0"); // Stellt sicher, dass alle Flaggs wieder auf false sind.

// SMS Relais 
int tasterpin = 22;

// Produktflaggen
bool product1flag = false;
bool product2flag = false;
bool product3flag = false;
bool product4flag = false;

// Bezahltflagge
bool paidflag = false;

NexTouch *nex_listen_list[] = 
{ 
  &initButton1,
  &initButton2,
  &initButton3,
  &initButton4,
  &initButton5,
  &initButton6,
  &initButton7,
  &initButton8, 
  &initButton9,
  NULL
};

void setup(){ 
  Serial.begin(9600); // Serielle Bibliothek einrichten
  while (!Serial);

  AFMSbot.begin(); // Shields werden gestartet
  AFMStop.begin();

  pinMode(tasterpin,INPUT_PULLUP);
  
  Serial.println("Start"); 

  initButton1.attachPop(initButton1PopCallback);
  initButton2.attachPop(initButton2PopCallback);
  initButton3.attachPop(initButton3PopCallback);
  initButton4.attachPop(initButton4PopCallback);
  initButton5.attachPop(initButton5PopCallback);
  initButton6.attachPop(initButton6PopCallback);
  initButton7.attachPop(initButton7PopCallback);
  initButton8.attachPop(initButton8PopCallback);
  initButton9.attachPop(initButton9PopCallback);
 
 
  Serial.print("Init Nextion Display... ");
  if(!next->nexInit(9600)){
    Serial.println("KO"); 
  }
  else{
    Serial.println("OK");
    delay(100);   
  }
}

void loop(){
  
  next->nexLoop(nex_listen_list);

  if (product1flag == true){    // Prüft ob Produkt1 gewählt wurde
    Serial.println("First loop p1");
    paidflag = digitalRead(tasterpin);
    
    if (!paidflag){   // Pürft ob bezahlt wurde
      Serial.println("Second loop p1");
      Spirale1sGo();
    }
  }

  if (product2flag == true){
    Serial.println("First loop p2");
    paidflag = digitalRead(tasterpin);
    
    if (!paidflag){
      Serial.println("Second loop p2");
      Spirale2sGo();
    }
  }

  if (product3flag == true){
    Serial.println("First loop p3");
    paidflag = digitalRead(tasterpin);
    
    if (!paidflag){
      Serial.println("Second loop p3");
      Spirale3sGo();
    }
  }

  if (product4flag == true){
    Serial.println("First loop p4");
    paidflag = digitalRead(tasterpin);
    
    if (!paidflag){
      Serial.println("Second loop p4");
      Spirale4sGo();
    }
  }  
}

void initButton1PopCallback(void *ptr){   // Button 1 == Produkt 1 kaufen
  Serial.println("Button 1");
  product1flag = true;
}
 
void initButton2PopCallback(void *ptr){
  Serial.println("Button 2");
  product2flag = true;
}

void initButton3PopCallback(void *ptr){
  Serial.println("Button 3");
  product3flag = true;  
}

void initButton4PopCallback(void *ptr){
  Serial.println("Button 4");
  product4flag = true;
}

void initButton5PopCallback(void *ptr){   // p1 == Produktseite 1 verlassen
   Serial.println("Exit p1"); 
   product1flag = false;
   
}
 
void initButton6PopCallback(void *ptr){
  Serial.println("Exit p2");
  product2flag = false;
}

void initButton7PopCallback(void *ptr){
  Serial.println("Exit p3");
  product3flag = false;
}

void initButton8PopCallback(void *ptr){
  Serial.println("Exit p3");
  product4flag = false;
}

void initButton9PopCallback(void *ptr){   // Stellt sicher, dass alle Flags auf false sind!
  Serial.println("Continue page 1(All false)"); 
  product1flag = false;
  product2flag = false;
  product3flag = false;
  product4flag = false;
}

void Spirale1sGo(){   // Produkt1 wird ausgeworfen
  Serial.println("Motor 1 run");
    myMotor1->step(400, BACKWARD, INTERLEAVE);
  product1flag = false;
}

void Spirale2sGo(){ 
  Serial.println("Motor 2 run");
  myMotor2->step(400, BACKWARD, INTERLEAVE);  
  product2flag = false;
}
  
void Spirale3sGo(){
  Serial.println("Motor 3 run");
  myMotor3->step(400, BACKWARD, INTERLEAVE);     
  product3flag = false;
}

void Spirale4sGo(){
  Serial.println("Motor 4 run");
  myMotor4->step(400, BACKWARD, INTERLEAVE);
  product4flag = false;
}