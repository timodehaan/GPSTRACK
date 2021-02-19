#include <Arduino.h>
#include <Wire.h>
// #include <clock.h>
#include "clock.cpp"
// #define DS3231_I2C_ADDRESS 0x68
// variables for the clock
Clock clock; // make the clock

// setup
void setup()
{
  //Wire.begin();
  Serial.begin(9600);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // clock.setDS3231time(0,55,14,6,19,2,21);
}

void loop()
{
  //clock.displayTime(); // display the real-time clock data on the Serial Monitor,
  Serial.println(clock.getDateTime());
  delay(1000);   // every second
}
