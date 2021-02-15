#include <Arduino.h>
#include <SD.h> //Load SD library
/* 
 * This code will be implemented in a tracking device
 * it needs to read, write and change data that is stored on the device
 * make multiple files
 * - settings
 * - routes
 * - personal collection
 * To Do
 * - println
 */

int chipSelect = 53; //chip select pin for the MicroSD Card Adapter             // proberbly gonna change that
File file;           // file object that is used to read and write data

// define the file names
#define SETTINGS "settings.txt"

class fileSym
{
private:
  // fields
  int pinModule;   //chip select pin for the MicroSD Card Adapter
  String fileName; // name of the file
  File file;       // the file object

public:
  // construnctor, pinModule default is 53
  fileSym(String fileName, int pinModule = 53)
  {
    this->pinModule = pinModule;
    this->fileName = fileName;   // save the file name
    pinMode(chipSelect, OUTPUT); // chip selected pin must be set to OUTPUT mode
    if (!SD.begin(pinModule))
    {                                                  // Initialize SD card
      Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
    }
    if (!SD.exists(fileName))
    {
      // create file
      file = SD.open(fileName, FILE_WRITE); // open "file.txt" to write data
      if (file)                             // if opened
      {
        file.print("This is the settings file\n"); // write number to file
        file.close();                            // close file
      }
      else
      {
        Serial.println("Could not make the file.");
      }
    }
  }
  // methods
  // read the file
  String read()
  {
    String rtnString;
    File file = SD.open(fileName, FILE_READ); // open "file.txt" to read data
    if (file)
    {
      char character;
      while ((character = file.read()) != -1)
      { // this while loop reads all data stored in the file
        rtnString += character;
      }
      file.close(); // close the file
    }
    else
    {
      Serial.println("Could not read the file.");
      return "";
    }
  }
  // write methods
  bool write(String data)
  {
    file = SD.open(fileName, FILE_WRITE); // open "file.txt" to write data
    if (file)                             // if opened
    {
      file.print(data); // write number to file
      file.close();     // close file
      return true;
    }
    else
    {
      Serial.println("Could not write to the file.");
      return false;
    }
  }
  bool write(int number)
  {
    // convert the number to string and write
    return write(String(number));
  }
};

void setup()
{
  Serial.begin(9600); // start serial connection to print out debug messages and data
}

void loop()
{
  // make the settings file
  static fileSym settings = fileSym(SETTINGS);
  settings.read();
  settings.write("A new row\n");
  delay(5000); // wait for 5000ms
}