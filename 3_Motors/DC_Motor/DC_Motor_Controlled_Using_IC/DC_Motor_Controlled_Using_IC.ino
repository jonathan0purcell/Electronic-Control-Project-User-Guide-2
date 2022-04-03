/*  DC Motor Controlled Using Integrated Chip (IC)
 *  
 *  The Arduino will use a relay (connected on one side) to control the direction
 *  of a DC motor (connected to a 9V battery on the other side of the relay)
 *  
 *  The integrated chip is the L293D (Quadruple Half-H Driver)
 *  
 *  A more detailed tutorial can be found at:
 *  https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/cop6RJ5idRi 
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Defining the pins for the motor
#define MOTOR_PWM_PIN 9 // The enable pin
#define MOTOR_CW_PIN 8
#define MOTOR_CCW_PIN 7
#define MOTOR_PWM_MAX 255 // Max speed
#define DELAY 2000 // The delay at which to change the direction

void setup() {
  // Setup the motor control pins to output
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_CW_PIN, OUTPUT);
  pinMode(MOTOR_CCW_PIN, OUTPUT);

  // Turns off the motors (Initial State)
  digitalWrite(MOTOR_CW_PIN, LOW);
  digitalWrite(MOTOR_CCW_PIN, LOW);
}

void controlDirection(const String DIRECTION){
  // Set the motor to the maximum speed
  analogWrite(MOTOR_PWM_PIN, MOTOR_PWM_MAX);

  if (DIRECTION=="Counter-clockwise") {
    // Make the motor turn counter-clockwise
    digitalWrite(MOTOR_CW_PIN, LOW);
    digitalWrite(MOTOR_CCW_PIN, HIGH);
  } else {
    // By default the motor will turn clockwise 
    digitalWrite(MOTOR_CW_PIN, HIGH);
    digitalWrite(MOTOR_CCW_PIN, LOW);
  }

    // Turn off the motors
    digitalWrite(MOTOR_CW_PIN, LOW);
    digitalWrite(MOTOR_CCW_PIN, LOW);
}

void loop() {
  // Make the motor turn clockwise
  controlDirection("");
  delay(DELAY);

  // Make the motor turn counter-clockwise
  controlDirection("Counter-clockwise");
  delay(DELAY);
}
