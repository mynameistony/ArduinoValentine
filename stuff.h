//TODO
//ADD WIFI CHARACTER FOR LCD

#ifndef Stuff_h
#define Stuff_h

#include <Arduino.h>

#include <SoftwareSerial.h>

#define MESSAGE_COUNT 10


class LCD {
  public:
    SoftwareSerial* lcd;
    
    boolean lightIsOn;
  
    LCD(int RxPin, int TxPin, int baud){
      
      lcd = new SoftwareSerial(RxPin,TxPin); //rx, tx
      
      lcd->begin(baud);
     
      lcd->write(12);
      lcd->write(22);      
            
    };
    
    void write(int theInt){
      lcd->write(theInt);  
    };
    
    void toggleLight(){
      if(lightIsOn)
        lightOff();
      else
        lightOn();
    
    };
    
    void lightOn(){
      lcd->write(17);
      lightIsOn = true;
    
    };
    
    void lightOff(){
      lcd->write(18);
      lightIsOn = false;
    };
    
    void setPos(unsigned int r,unsigned int c){
      if(r == 0)
        lcd->write(128 + c);
      else
        if(r == 1)
          lcd->write(148 + c);
        else{} 
  
     };
     
     void clear(){
       lcd->write(12); 
     };
     
     void print(String theString){
        lcd->print(theString); 
     };
     
     void print(int theInt){
        lcd->print(theInt); 
     };
     void print(unsigned long theLong){
        lcd->print(theLong); 
     };
     void print(unsigned long theLong, int format){
        lcd->print(theLong, HEX); 
     };
     
     
    
    
  
};

class Valentines{
  public:
  int buttonPin;
  int LEDpin;
  int messageCount;
  int trigPin;
  int echoPin;
  
  
  LCD* lcd;
  

  
  char* messages[MESSAGE_COUNT]{
    "I love you!", "You're         beautiful", "You're         wonderful", "You're perfect", "Be my          valentine", "Don't ever     change", "TR + HP 4-ever", "Be Mine", "I'm crazy for  you", "You light up my heart"
  
  };
  
  Valentines(int newRxPin, int newTxPin, int newBaud, int newTrigPin, int newEchoPin, int newLED, int newButton){
      messageCount = MESSAGE_COUNT;
      trigPin = newTrigPin;
      echoPin = newEchoPin;

      lcd = new LCD(newRxPin,newTxPin,newBaud);
      
      buttonPin = newButton;
      
      LEDpin = newLED;
      
      pinMode(newTrigPin, OUTPUT);
      pinMode(newEchoPin, INPUT);

      
      pinMode(buttonPin,INPUT_PULLUP);      
  };  
  
  void rickRoll(){
    lcd->lightOn();
    
    lcd->clear();
    lcd->print("Never gonna give you up");    
    for(int i = 0; i < 255; i++){
      setFade(i);
      delay(10); 
    }
      
//    delay(2000);
    lcd->clear();
    lcd->print("Never gonna let you down");
    for(int i = 255; i > 0; i--){
      setFade(i);
      delay(10); 
    }
      
//    delay(2000);

    lcd->clear();
    lcd->print("Never gonna run around");
    for(int i = 0; i < 255; i++){
      setFade(i);
      delay(10); 
    }
      
//''    delay(1000);

    lcd->clear();
    lcd->print("and desert you");
    for(int i = 255; i > 0; i--){
      setFade(i);    
      delay(10); 
    }      
//    delay(2000);
    lcd->clear();
    lcd->print("Never gonna make you cry");
    for(int i = 0; i < 255; i++){
      setFade(i);
      delay(10); 
    }
      
    //delay(2000);
    lcd->clear();
    lcd->print("Never gonna say goodbye");
    for(int i = 255; i > 0; i--){
      setFade(i);    
      delay(10); 
    }
      
//    delay(2000);

    lcd->clear();
    lcd->print("Never gonna tell a lie");
    for(int i = 0; i < 255; i++){
      setFade(i);
      delay(10); 
    }
      
//    delay(1000);    

    lcd->clear();
    lcd->print("and hurt you :P");
    for(int i = 0; i < 255; i++){
      setFade(i);
      delay(10); 
    }
 
//    delay(2000);    

    lcd->lightOff();      

    for(int i = 255; i >= 0; i--){
      setFade(i);    
      delay(10); 
    }
      
  }
    
  void setFade(int newFade){
    analogWrite(LEDpin,newFade);
  };
  
  long getDistance(){
    long duration, distance;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPin, HIGH);
    //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;  
  
    return distance;  
  };
  
  boolean getButtonState(){
    return !digitalRead(buttonPin);
  };
  
  char* printRandomMessage(int magicNumber, boolean withNoise){
    if(magicNumber == 420){
      rickRoll();
      return "RickRolled";
    }

    if(withNoise){    
     lcd->write(213);
     lcd->write(228);
     
     lcd->write(213);
     lcd->write(223);
     
     lcd->write(212);
     lcd->write(227);

     lcd->write(213);
     lcd->write(220); 
    }
    char* thisMessage = messages[random(messageCount)];
        
    lcd-> clear();
    
    lcd->lightOn(); 
    
    lcd->write(1);
    lcd->print(thisMessage);
    lcd->write(1);
    
    for(int i = 0; i < 255; i++){
      analogWrite(9,i);
      delay(10);
    }
    
    for(int i = 255; i > 0; i--){
      analogWrite(9,i);
      delay(10);
    }
    
    analogWrite(9,0);
    
    lcd->lightOff();
      
    lcd->clear();
        
    return thisMessage;
      
  };
  
  void printDisplay(int thisHour, int thisMinute, boolean thisAM){//, int wifiStatus){
    lcd->clear();
        
/*
    if(!wifiStatus)
      lcd->print("!");
    else
       lcd->write(2); 
*/   
//    lcd->setPos(0,8);
    
    if(thisHour < 10)
      lcd->print(" ");
    
    lcd->print(thisHour);
    lcd->print(":");
    lcd->print(thisMinute);
    
    if(thisAM)
      lcd->print("AM");
    else
      lcd->print("PM");
      
  }
  
  void printMessage(int index){
    if(index > messageCount){
 
    lcd->lightOn(); 
    
    lcd->write(1);
    lcd->print(messages[index]);
    lcd->write(1);
    
    for(int i = 0; i < 255; i++){
      analogWrite(9,i);
      delay(10);
    }
    
    for(int i = 255; i > 0; i--){
      analogWrite(9,i);
      delay(10);
    }
    
    analogWrite(9,0);
    
    lcd->lightOff();
      
    lcd->clear();  
      
    }
    
  };
  
  void createHeart(){
   lcd->write(249);
 
 lcd->write(10);
 lcd->write(31);
 lcd->write(31);
 lcd->write(31);
 
 lcd->write(14); 
 lcd->write(14);
 lcd->write(4);
 lcd->write(0);
};

void powerOn(){
   createHeart();
   
   lcd->clear();
   lcd->lightOn();
   

   lcd->write(1);
   lcd->write(1);
   lcd->write(1);   
   lcd->print("I Love You");
   lcd->write(1);   
   lcd->write(1);
   lcd->write(1);   
   
   for (int i = 0; i < 16; i++)
     lcd->write(1);
     
    for(int i = 0; i < 255; i++){
      analogWrite(9,i);
      delay(5);
    }
    
    for(int i = 255; i > 0; i--){
      analogWrite(9,i);
      delay(5);
    }
    
    analogWrite(9,0);

   
   lcd->clear();
   lcd->lightOff();
    
    
  };
  
  
};
#endif
