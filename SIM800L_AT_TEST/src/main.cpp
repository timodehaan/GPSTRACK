#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Sim800l(10,11);
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("test om te kijken of die het doet");
  Sim800l.begin(9600);
}

void loop() {
 
 while(Sim800l.available()){
  Serial.write(Sim800l.read());
 }

  
 while(Serial.available()){
  Sim800l.write(Serial.read());
 }

}