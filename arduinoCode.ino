#include <SoftwareSerial.h>
#define READING_DELAY 5

//#define RED '0'
//#define BLUE '1'
//#define GREEN '2'
//#define OFF '3'
//#define LED_STATUS '4'
//#define OK '5'
//#define ERR '6'
//#define INTENSITY= 

//SoftwareSerial Serial(2,3); //Instantiating serrial for comunicating with Serial module. (Rx, Tx)

//Setting the pin numbers
const int pwmPin = 6;
const int redPin    = 7;
const int greenPin  = 8;
const int bluePin   = 9;

int intensity = 0;    //LED light intensity

enum color{
  off,
  red,
  blue,
  green
  
} ledState;

void setup() {

  delay(1000);
  
  Serial.begin(115200);
  pinMode(pwmPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //setting the initial state of the pins
  analogWrite(pwmPin, intensity);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  

}

void loop() {
  
  //while(!Serial.available()); //Wait for esp to send commands

  //delay(READING_DELAY); //Wait for buffer to fill
  
  String respond = Serial.readStringUntil('\n');

  if(respond.length() != 0){
    if(respond.indexOf("LED_STATUS") >= 0){
      if(ledState == off)
        Serial.println("OFF");
        
      else if(ledState == red)
        Serial.println("RED");
  
      else if(ledState == green)
        Serial.println("GREEN");
  
      else if(ledState == blue)
        Serial.println("BLUE");
      
    }
  
    else if(respond.indexOf("RED") >= 0){
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      ledState = red;
      Serial.println("OK");
    }
    
    else if(respond.indexOf("GREEN") >= 0){
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
      ledState = green;
      Serial.println("OK");
    }
  
    else if(respond.indexOf("BLUE") >= 0){
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      ledState = blue;
      Serial.println("OK");
    }
  
    else if(respond.indexOf("OFF") >= 0){
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      ledState = off;
      Serial.println("OK");
    }
  
    else if(respond.indexOf("INTENSITY=") >= 0){
      respond = strtok(respond.c_str(), "=");       //Skip the "INTENSITY" 
      respond = strtok(NULL, "=");
      intensity = respond.toInt();
      analogWrite(pwmPin, intensity);
      Serial.println("OK");
    }
    
    else{
      Serial.println("ERR");
    } 
  }
}
