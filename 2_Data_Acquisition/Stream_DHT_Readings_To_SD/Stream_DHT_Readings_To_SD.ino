/* Temperature and Humidity Printing to Serial (Saved to SD card)
 *  
 *  The Arduino will use the DHT11 Temperature and Humidity sensor as input,
 *  and then record the values to a CSV file on the SD card.
 *  
 *  The wiring for this project can be found at:
 *  -----
 *  
 *  The schematic drawing for this project can be found at:
 *  -----
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  -----
*/

// Include the adafruit sensor library and the library for the DHT11 sensor
#include <Adafruit_Sensor.h>  // Need to download this from Library Manager ("Adafruit Unified Sensor")
#include <DHT.h>              // Need to download from "arduino.cc/reference/en/libraries/dht-sensor-library"

// Include the libraries for the SD card
#include <SPI.h>
#include <SD.h>

// The characteristics of the DHT11 sensor (The type and the digital pin on the arduino)
#define DHTTYPE DHT11
#define DHT_PIN 2

// The amount of time the program waits before reading from the sensor again (in milliseconds)
#define SENSOR_READING_DELAY 2000

// The DHT11 sensor object from the library - can then be used to call functions
DHT dht = DHT(DHT_PIN, DHTTYPE);

// File name of the CSV
const String CSV_FILE_NAME = "DHT_READINGS.csv";

// File object for the CSV file we will be writing to
// Open the file and have write access to it
File csvFile = SD.open(CSV_FILE_NAME, FILE_WRITE);;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Begin the DHT11 sensor -- starts reading values, without this, no readings will take place
  dht.begin();

  // Checks to see if the SD card initialized well (Pin 4 is default Chip Select (CS))
  Serial.println("Initialiazing SD card...");
  
  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    while (1);
  }

  Serial.println("Initilization done.");
}

// Prints the temperature and humidity teadings in CSV format in the CSV file on the SD card
void printReadingInCSVFormat(const float DHT_HUMIDITY, const float DHT_TEMPERATURE) {
  csvFile.print("Humidity (%),");
  csvFile.print(DHT_HUMIDITY, 2);
  csvFile.print(",");
  csvFile.print("Temperature (C),");
  csvFile.print(DHT_TEMPERATURE, 2);
  csvFile.println(",");
} 

void loop() {
  // Temporary variables to store humidity and temperature from DHT11
  // Keeping it as a local scope since it's not used elsewhere
  const float DHT_HUMIDITY = dht.readHumidity();        // Reads humidity
  const float DHT_TEMPERATURE = dht.readTemperature();  // Reads temperature in celcius

  // Make sure there's a valid reading from the sensor
  if (isnan(DHT_HUMIDITY) || isnan(DHT_TEMPERATURE)) {
    Serial.println("Failed to read from DHT sensor!\n");
  } else {
    // If the file opened okay, write to it
    if (csvFile) {
      printReadingInCSVFormat(DHT_HUMIDITY, DHT_TEMPERATURE);
    } else {
      Serial.println("Error opening ");
      Serial.print(CSV_FILE_NAME);
      Serial.println();
    }
  }
  
  // Delays by a certain amount of time specified at the start of the program
  delay(SENSOR_READING_DELAY);
}
