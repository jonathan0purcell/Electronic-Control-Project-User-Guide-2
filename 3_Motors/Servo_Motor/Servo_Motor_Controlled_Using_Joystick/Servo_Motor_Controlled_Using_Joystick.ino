/*  Servo Motor Controlled Using Joystick
 *  
 *  The Arduino will use a joystick to control the angle of the servo motor
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/1MGP375wDgV 
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Include the library for the servo motor
#include <Servo.h>

// Defining the pins for the motor
#define SERVO_PIN 9
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180

// Defining the pins for the joystick
#define JOYSTICK_X_PIN A0
#define JOYSTICK_X_MIN 0
#define JOYSTICK_X_MAX 1023

// The delay between servo movements
#define DELAY 100

// The servo object to be able to call the methods
Servo servo;

void setup() {
  // Attach the servo to the given pin
  servo.attach(SERVO_PIN);
}

void loop() {
  // Get the serial reading of the joystick x-axis 
  const int JOYSTICK_X_VAL = analogRead(JOYSTICK_X_PIN);

  // Map the serial reading to between 0 and 180
  // Turning joystick left makes servo go left, turning it right makes servo go right
  const int SERVO_ANGLE = map(JOYSTICK_X_VAL, JOYSTICK_X_MIN, JOYSTICK_X_MAX,
    SERVO_MAX_ANGLE, SERVO_MIN_ANGLE);
  
  // Set the angle of the servo motor (Must be between 0 and 180 degrees)
  servo.write(SERVO_ANGLE); 

  // Pause the program for DELAY millioseconds (Specified above)
  delay(DELAY);
}
