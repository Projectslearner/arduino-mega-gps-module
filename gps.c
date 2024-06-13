/*
    Project name : GPS Module
    Modified Date: 13-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-mega-gps-module
*/

#include <SoftwareSerial.h>

// Define the RX and TX pins for SoftwareSerial
const int RXPin = 10;  // RX pin of Arduino Mega connected to TX pin of GPS module
const int TXPin = 11;  // TX pin of Arduino Mega connected to RX pin of GPS module

// Create a SoftwareSerial object
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  // Start serial communication with a baud rate of 9600
  Serial.begin(9600);
  
  // Start SoftwareSerial communication with GPS module
  gpsSerial.begin(9600);
}

void loop() {
  // Read data from GPS module if available
  while (gpsSerial.available() > 0) {
    // Check if data starts with '$GPGGA' (this is a standard NMEA sentence for GPS data)
    if (gpsSerial.find("$GPGGA")) {
      // Read latitude data
      String latitude = gpsSerial.readStringUntil(',');
      
      // Skip 2 fields (time and latitude indicator)
      for (int i = 0; i < 2; i++) {
        gpsSerial.readStringUntil(',');
      }
      
      // Read longitude data
      String longitude = gpsSerial.readStringUntil(',');
      
      // Skip 4 fields (longitude indicator, fix quality, satellites, and HDOP)
      for (int i = 0; i < 4; i++) {
        gpsSerial.readStringUntil(',');
      }
      
      // Read altitude data
      String altitude = gpsSerial.readStringUntil(',');
      
      // Print GPS data to Serial Monitor
      Serial.print("Latitude: ");
      Serial.println(latitude);
      Serial.print("Longitude: ");
      Serial.println(longitude);
      Serial.print("Altitude: ");
      Serial.println(altitude);
      
      // Wait for a moment before reading the next data
      delay(2000);
    }
  }
}
