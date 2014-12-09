#include <Servo.h> 

Servo yourservo;  // create servo object to control a servo 
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position 
int millisec=180;
double sens1=0;
double sens2=0;
double sens3=0;
void setup() 
{ 
  yourservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 

void loop() {
  while(digitalRead(4)){
    yourservo.write(pos);
    //delay(5);
  }
    yourservo.write(180);
    delay(500);
  yourservo.write(0);
  while(digitalRead(11)&&digitalRead(4)){
    millisec+=10;
    delay(10);
    Serial.println(millisec);
  }
  sens1=((double)millisec)/1000;
  /*millisec=0;
  while(digitalRead(10)&&digitalRead(4)){
    millisec+=10;
    delay(10);
    Serial.println(millisec);
  }
  sens2=((double)millisec)/1000;
  millisec=0;
  while(digitalRead(11)&&digitalRead(4)){
    millisec+=10;
    delay(10);
    Serial.println(millisec);
  }
  sens3=((double)millisec)/1000;*/
  millisec=0;
  Serial.println("sens1= "+String(sens1));/*
  Serial.println("sens2= "+String(sens2));
  Serial.println("sens3= "+String(sens3));
  Serial.println("total= "+String(sens1+sens2+sens3));*/
  delay(1000);
}


