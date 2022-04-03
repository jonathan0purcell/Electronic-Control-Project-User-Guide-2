/*  Temperature and Humidity Printing to Serial (Saved to Excel)
 *  
 *  The Arduino will use the DHT11 Temperature and Humidity sensor as input,
 *  and then display the recorded values on the serial monitor.
 *  
 *  The readings from the serial monitor will be in a comma seperated value 
 *  format (CSV) and can be streamed into excel and saved to a .CSV file and 
 *  then graphed.
 *  
 *  Make sure to enable to Data Streamer add-in on Excel
 *  https://support.microsoft.com/en-us/office/enable-the-data-streamer-add-in-70052b28-3b00-41e7-8ab6-8a9f142dffeb
 *  
 *  The tutorial to set up the reading can be found at:
 *  https://create.arduino.cc/projecthub/HackingSTEM/stream-data-from-arduino-into-excel-f1bede
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/0cpIcgdUMxS
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Include the adafruit sensor library and the library for the DHT11 sensor
#include <Adafruit_Sensor.h>  // Need to download this from Library Manager ("Adafruit Unified Sensor")
#include <DHT.h>              // Need to download from "arduino.cc/reference/en/libraries/dht-sensor-library"

// The characteristics of the DHT11 sensor (The type and the digital pin on the arduino)
#define DHTTYPE DHT11
#define DHT_PIN 2

// The amount of time the program waits before reading from the sensor again (in milliseconds)
#define SENSOR_READING_DELAY 2000

// The DHT11 sensor object from the library - can then be used to call functions
DHT dht = DHT(DHT_PIN, DHTTYPE);

void setup() {
  // Start the serial communication with a baud rate of 9600 bps
  // This serial communication will be streamed into Excel
  Serial.begin(9600);
  
  // Begin the DHT11 sensor -- starts reading values, without this, no readings will take place
  dht.begin();
}

// Makes the formatting of the printing nice
void printReadingInCSVFormat(const float DHT_HUMIDITY, const float DHT_TEMPERATURE) {
  Serial.print("Humidity (%),");
  Serial.print(DHT_HUMIDITY, 2);
  Serial.print(",");
  Serial.print("Temperature (C),");
  Serial.print(DHT_TEMPERATURE, 2);
  Serial.println(",");
} 

void loop() {
  // Temporary variables to store humidity and temperature from DHT11
  // Keeping it as a local scope since it's not used elsewhere
  const float DHT_HUMIDITY = dht.readHumidity();        // Reads humidity
  const float DHT_TEMPERATURE = dht.readTemperature();  // Reads temperature in celcius

  if (isnan(DHT_HUMIDITY) || isnan(DHT_TEMPERATURE)) {
    Serial.println("Failed to read from DHT sensor!\n");
  } else {
    printReadingInCSVFormat(DHT_HUMIDITY, DHT_TEMPERATURE);
  }
  
  // Delays by a certain amount of time specified at the start of the program
  delay(SENSOR_READING_DELAY);
}
