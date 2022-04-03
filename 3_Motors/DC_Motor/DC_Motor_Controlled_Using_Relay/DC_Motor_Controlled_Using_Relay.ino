/*  DC Motor Controlled Using Relay
 *  
 *  The Arduino will use a relay (connected on one side) to control a
 *  DC motor (connected to a 9V battery on the other side of the relay)
 *  
 *  A pinout for the relay can be found at:
 *  https://components101.com/sites/default/files/component_pin/Relay-Pinout.png
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/6r4gyh5adlb 
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Defining the pins for the motor
#define RELAY_PIN 3
#define DELAY 2000

void setup() {
  // Setup the motor control pins to output
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Turns the relay on, which closes the circuit between DC motor and battery
  digitalWrite(RELAY_PIN, HIGH);
  
  // Pauses the program for 2 seconds
  delay(DELAY);
  
  // Turns the relay off, which opens the circuit between DC motor and battery
  digitalWrite(RELAY_PIN, LOW);
  
  delay(DELAY); // Wait 2 seconds
}
