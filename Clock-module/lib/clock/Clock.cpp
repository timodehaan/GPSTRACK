#include "Clock.h"

// the constructor
Clock::Clock(int adress)
{
    this->adress = adress;
    Wire.begin();
}

// Convert normal decimal numbers to binary coded decimal
byte Clock::decToBcd(byte val)
{
    return ((val / 10 * 16) + (val % 10));
}
// Convert binary coded decimal to normal decimal numbers
byte Clock::bcdToDec(byte val)
{
    return ((val / 16 * 10) + (val % 16));
}

void Clock::setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
    // sets time and date data to DS3231
    Wire.beginTransmission(adress);
    Wire.write(0);                    // set next input to start at the seconds register
    Wire.write(decToBcd(second));     // set seconds
    Wire.write(decToBcd(minute));     // set minutes
    Wire.write(decToBcd(hour));       // set hours
    Wire.write(decToBcd(dayOfWeek));  // set day of week (1=Sunday, 7=Saturday)
    Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
    Wire.write(decToBcd(month));      // set month
    Wire.write(decToBcd(year));       // set year (0 to 99)
    Wire.endTransmission();
}
void Clock::readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
    Wire.beginTransmission(adress);
    Wire.write(0); // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(adress, 7);
    // request seven bytes of data from DS3231 starting from register 00h
    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
    *dayOfWeek = bcdToDec(Wire.read());
    *dayOfMonth = bcdToDec(Wire.read());
    *month = bcdToDec(Wire.read());
    *year = bcdToDec(Wire.read());
}
void Clock::displayTime()
{
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    // retrieve data from DS3231
    readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    // send it to the serial monitor
    Serial.print(hour, DEC);
    // convert the byte variable to a decimal number when displayed
    Serial.print(":");
    if (minute < 10)
    {
        Serial.print("0");
    }
    Serial.print(minute, DEC);
    Serial.print(":");
    if (second < 10)
    {
        Serial.print("0");
    }
    Serial.print(second, DEC);
    Serial.print(" ");
    Serial.print(dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(month, DEC);
    Serial.print("/");
    Serial.print(year, DEC);
    Serial.print(" Day of week: ");
    // make array
    Serial.println(dayNames[dayOfWeek]);
}

int Clock::getSec()
{
    byte sec, temp;
    // retrieve data from DS3231
    readDS3231time(&sec, &temp, &temp, &temp, &temp, &temp, &temp);
    return sec;
}
int Clock::getMin()
{
    byte min, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &min, &temp, &temp, &temp, &temp, &temp);
    return min;
}
int Clock::getHour()
{
    byte hour, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &hour, &temp, &temp, &temp, &temp);
    return hour;
}
int Clock::getDay()
{
    byte day, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &temp, &day, &temp, &temp);
    return day;
}
int Clock::getMonth()
{
    byte month, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &temp, &temp, &month, &temp);
    return month;
}
int Clock::getYear()
{
    byte year, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &temp, &temp, &temp, &year);
    return 2000 + year;
}
int Clock::getDayOfWeek()
{
    byte dayOfWeek, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &dayOfWeek, &temp, &temp, &temp);
    return dayOfWeek;
}
String Clock::getTime()
{
    byte second, minute, hour, temp;
    // retrieve data from DS3231
    readDS3231time(&second, &minute, &hour, &temp, &temp, &temp, &temp);
    // make time format "08:30"
    String rtnTime = "";
    if (hour < 10)
    {
        rtnTime += "0";
    }
    rtnTime += String(hour) + ":";
    if (minute < 10)
    {
        rtnTime += "0";
    }
    rtnTime += String(minute);
    return rtnTime;
}
String Clock::getDate()
{
    byte temp, day, month, year;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &temp, &day, &month, &year);
    // make date format 19/2/21
    return String(day) + "/" + String(month) + "/" + String(year);
}
String Clock::getDateTime()
{
    byte second, minute, hour, dayOfWeek, day, month, year;
    // retrieve data from DS3231
    readDS3231time(&second, &minute, &hour, &dayOfWeek, &day, &month, &year);
    // make time format "08:30 19/2/21"
    String rtnTime = "";
    if (hour < 10)
    {
        rtnTime += "0";
    }
    rtnTime += String(hour) + ":";
    if (minute < 10)
    {
        rtnTime += "0";
    }
    rtnTime += String(day) + "/" + String(month) + "/" + String(year);
    return rtnTime;
}

String Clock::getDayOfWeekSTR()
{
    byte dayOfWeek, temp;
    // retrieve data from DS3231
    readDS3231time(&temp, &temp, &temp, &dayOfWeek, &temp, &temp, &temp);
    return dayNames[dayOfWeek];
}

