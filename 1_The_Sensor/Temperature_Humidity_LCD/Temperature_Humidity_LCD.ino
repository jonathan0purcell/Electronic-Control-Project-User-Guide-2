/* Temperature and Humidity Displayed on LCD
 *  
 *  The Arduino will use the DHT11 Temperature and Humidity sensor as input,
 *  and then display the recorded values on a Liquid Crystal Display (LCD).
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/jFypArMiHk7 
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Include the libraries for the adafruit sensors, DHT11 sensor and the LCD
#include <Adafruit_Sensor.h>  // Need to download this from Library Manager ("Adafruit Unified Sensor")
#include <DHT.h>              // Need to download from "arduino.cc/reference/en/libraries/dht-sensor-library"
#include <LiquidCrystal.h>

// The characteristics of the DHT11 sensor (The type and the digital pin on the arduino)
#define DHT_TYPE DHT11
#define DHT_PIN 6

// Characteristics of the LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// The amount of time the program waits before reading from the sensor again (in milliseconds)
#define SENSOR_READING_DELAY 2000

// The DHT11 sensor object from the library - can then be used to call functions
DHT dht = DHT(DHT_PIN, DHT_TYPE);

/* LCD pins and their connections
 *  
 * VSS to GND
 * VDD to +5V
 * V0 to ground (connect to potentiometer or resistor to dim the whiteness on the squares 2k)
 * RS to pin 12
 * RW to GND
 * E to pin 11
 * D4 to pin 5
 * D5 to pin 4
 * D6 to pin 3
 * D7 to pin 2
 * A to +5V (Anode)
 * K to GND (Kathode)
*/

// Variables for the LCD pins
const int LCD_RS = 12;  // Reset pin
const int LCD_E = 11;   // Enable Pin
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;

// The LiquidCrystal object from the library - can then be used to call functions
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // Start the serial communication with a baud rate of 9600 bps
  Serial.begin(9600);

  // Begin the DHT11 sensor -- starts reading values, without this, no readings will take place
  dht.begin();
  
  // Begin the LCD with 16 columns and 2 rows (These are the specs of the given LCD)
  lcd.begin(LCD_COLUMNS, LCD_ROWS);

  // Set the cursor on the LCD at the origin (row 0, column 0) - starts writing from there
  lcd.setCursor(0,0);
}

// Function used to update the DHT11 readings -- used to clean loop function
void printReadingOnLCD(const float DHT_HUMIDITY, const float DHT_TEMPERATURE, boolean DHT_ERR) {
  // Clearing the line
  lcd.print("                ");

  // Set the cursor to te first row, first character
  lcd.setCursor(0, 0);
  
  // Displayed ERROR on the LCD if the DHT11 can't read the tempeature and humidity
  if (DHT_ERR) {
    lcd.print("DHT11 ERROR");
  } else {
    // If there is no error then display the temperature and humidity on the LCD
    lcd.print("Temp.: ");           // Prints the temperature in the first row
    lcd.print(DHT_TEMPERATURE);
    lcd.setCursor(0, 1);            // Sets the cursor to the second row, first character
    lcd.print("Humidity: ");        // Prints the humidity in the second row
    lcd.print(DHT_HUMIDITY);
  }
}

void loop() {  
  // Temporary variables to store humidity and temperature from DHT11
  // Keeping it as a local scope since it's not used elsewhere
  const float DHT_HUMIDITY = dht.readHumidity();
  const float DHT_TEMPERATURE = dht.readTemperature();  // Reads temperature in celcius

  // Make sure there's a valid reading for the temperature and humidity
  if (isnan(DHT_HUMIDITY) || isnan(DHT_TEMPERATURE)) {
    // If the program reaches here then the wiring can be off
    // or the DHT11 sensor can be malfuncioning
    printReadingOnLCD(0, 0, true);
  } else {
    // Use the printReadingOnLCD() function to print the output neatly on the LCD
    printReadingOnLCD(DHT_HUMIDITY, DHT_TEMPERATURE, false);
  }

  // Delays by a certain amount of time specified at the start of the program
  delay(SENSOR_READING_DELAY);
}
