/* Temperature and Humidity Displayed on Serial Monitor
 *  
 *  The Arduino will use the DHT11 Temperature and Humidity sensor as input,
 *  and then displayed the recorded values on the serial monitor.
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/6PL8MxEj6j3 
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
  Serial.begin(9600);

  // Begin the DHT11 sensor -- starts reading values, without this, no readings will take place
  dht.begin();
}

// Makes the formatting of the printing nice
void cleanPrint(const String title, const float value, const String nl) {
  Serial.print(title);
  Serial.print(value, 3);
  Serial.print(nl);
}

void loop() {
  // Temporary variables to store humidity and temperature from DHT11
  // Keeping it as a local scope since it's not used elsewhere
  const float DHT_HUMIDITY = dht.readHumidity();        // Reads humidity
  const float DHT_TEMPERATURE = dht.readTemperature();  // Reads temperature in celcius

  // Make sure there's a valid reading for the temperature and humidity
  if (isnan(DHT_HUMIDITY) || isnan(DHT_TEMPERATURE)) {
    // If the program reaches here then the wiring can be off
    // or the DHT11 sensor can be malfuncioning
    Serial.println("Failed to read from DHT sensor!\n");
  } else {
    // Use the cleanPrint() function to print the output neatly on the serial monitor
    cleanPrint("Humidity: ", DHT_HUMIDITY, "%\n");
    cleanPrint("Temperature: ", DHT_TEMPERATURE, "°C\n\n"); 
  }

  // Delays by a certain amount of time specified at the start of the program
  delay(SENSOR_READING_DELAY);
}
