// this is my value added coding
// please see the comments below

// 03/02/16
// MT- Temp/humidity sensor and LCD Integration.
// This is the parent code for the MT.
// In this code we read temp and humidity sensor data
// and output the results to an LCD.
// Special thanks go to Rob Tillart, for the base .h and .cpp
// files required to read the sensor data.

#include "dht.h"  // Include “dht” header file created by Rob Tillart
dht DHT;    // Create a “dht” object from the header file
#define DHT11_PIN 5 // Designate digital pin #5 for sensor communication

const int TxPin = 6;    // Designate digital pin #6 for LCD serial communication
#include <SoftwareSerial.h> // Include “SoftwareSerial” header file from the Arduino Library
SoftwareSerial mySerial = SoftwareSerial(255, TxPin); // Creating a “SoftwareSerial” objecct

// The following  void setup method prints to the serial monitor
// This is used for testing sensor readings
void setup()
{
  Serial.begin(115200); // Establish serial communications
  Serial.println("DHT TEST PROGRAM ");  // Print line to serial monitor
  Serial.print("LIBRARY VERSION: ");  // Print line to serial monitor
  Serial.println(DHT_LIB_VERSION);  // Print line to serial monitor
  Serial.println();       // Print line to serial monitor
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)"); // Print line to serial monitor

  pinMode(TxPin, OUTPUT); // Define pin as output
  digitalWrite(TxPin, HIGH);  // Start signal to combination sensor
}

// This is the main loop for checking the validity of the data from the sensor
// as well as reading and reporting the data from the sensor and writing it to the LCD
void loop()
{
  // Read data loop
  Serial.print("DHT11, \t");  // Print line to serial monitor
  int chk = DHT.read11(DHT11_PIN);  // Integer variable “chk” set to the read value
  switch (chk)  // Checking the value of “chk” and switching based on the result
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");  // Sensor reading is OK
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");  // Sensor reading has checksum error
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");    // Sensor reading has timeout error
      break;
    default:
      Serial.print("Unknown error,\t"); // Sensor reading has unknown error
      break;
  }
  // Display data loop
  Serial.print(DHT.humidity, 1);  // Display humidity
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1); // Display temperature
  // Note, the above code is strictly to send readings to the serial monitor, for testing purposes


  mySerial.begin(9600); // Set baud rate and begin serial port communication to LCD
  delay(100); // Short 10ms delay before writing first command
  mySerial.write(12); // Sending clear command to screen
  mySerial.write(17);                 // Sending turn backlight on command to screen
  delay(5); // Short required 5 ms delay
  mySerial.print("Temp: "); // First line is for the temperature
  mySerial.print((((DHT.temperature * 9 / 5)) + 32)); // First line print the converted temperature
  mySerial.print("F");  // First line add the units
  mySerial.write(13); //Sending form feed to the screen
  mySerial.print("Humid: ");  // Second line is the humidity
  mySerial.print(DHT.humidity); // Second print the humidity
  mySerial.print("%  ");  //  Second line add the units
  //mySerial.write(13); // Sending form feed to the screen
  mySerial.write(212);                // Sending quarter note command to the LCD
  //mySerial.write(220);    // Musical note that is commented out
  delay(3000);    // Short 3000 ms delay
  //mySerial.write(18);   // Turn backlight off command that is commented out

  delay(2000);    // Short 3000 ms delay
}


