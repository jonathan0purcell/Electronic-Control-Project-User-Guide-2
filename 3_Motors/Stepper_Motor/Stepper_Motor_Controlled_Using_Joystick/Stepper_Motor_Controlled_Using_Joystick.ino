/*  Stepper Motor Controlled Using Joystick
 *  
 *  The Arduino will use a joystick to control the direction of the servo motor
 *  
 *  The wiring, schematic and simulation for this project can be found at:
 *  https://www.tinkercad.com/things/0u7wyWt8UPi 
 *  
 *  Create 2 April, 2022
 *  by Jonathan Purcell
 *  
 *  This code, amoung others, can be found in the GitHub repository:
 *  https://github.com/jonathan0purcell/Electronic-Control-Project-User-Guide-2.git
*/

// Include the library for the stepper motor
#include <Stepper.h>

/* Defining the pins for the motor and joystick */

// Change this to fit the number of steps per revolution (Amount of rotate, 2048 is 360 degrees)
#define STEPS_PER_REVOLUTION 2048

// Adjustable range of 28BYJ-48 stepper is 0~17 RPM (Speed of rotation)
#define ROLE_PER_MINUTE 17

// The home position (default value when not touching the joystick) for x is 436
#define JOYSTICK_HOME_X 436

// The amount the stick has to be pushed from the home position (higher tolerance,
// the more you will need to move the joystick to the side to move the stepper motor)
#define JOYSTICK_TOLERANCE 50

// The X-axis pin on the joystick connected to analog pin A0
#define JOYSTICK_X_PIN A0

// Small delay since want to update as frequently as possible
#define DELAY 100

// Initialize the stepper library on pins 8 through 11
Stepper stepper(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

void setup() {
  // Set the speed of the stepper motor
  stepper.setSpeed(ROLE_PER_MINUTE);
}

void loop() {
  // Get the serial reading of the joystick x-axis (between 0 and 1023)
  const int JOYSTICK_X_VAL = analogRead(JOYSTICK_X_PIN);

  // Joystick is being pushed left
  if (JOYSTICK_X_VAL < (JOYSTICK_HOME_X-JOYSTICK_TOLERANCE)) {
    // Step one revolution in one direction (Clockwise)
    stepper.step(-STEPS_PER_REVOLUTION);    
  } else if (JOYSTICK_X_VAL > (JOYSTICK_HOME_X+JOYSTICK_TOLERANCE)) {
    // Joystick is being pushed right
    // Step one revolution in one direction (Counter-clockwise)
    stepper.step(STEPS_PER_REVOLUTION);
  }

  // Pause the program for DELAY millioseconds (Specified above)
  delay(DELAY);
}
