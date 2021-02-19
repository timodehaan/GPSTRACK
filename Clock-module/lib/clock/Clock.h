#ifndef Clock_h
#define Clock_h
#include "Arduino.h"
#include "Wire.h"

class Clock
{
private:
    int adress; // the I2C adress to the DS3231(rtc-module)
    // funtions
    byte decToBcd(byte val);
    byte bcdToDec(byte val);

public:
    // constructor
    Clock(int adress =  0x68);
    // functions
    void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
    void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);
    void displayTime();
    // test
    String getDay();
};
#endif