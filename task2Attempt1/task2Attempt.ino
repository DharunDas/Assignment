#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

//#define LED 13
#define QTR_THRESHOLD 1500 // microseconds

// these might need to be tuned for different motor types
#define REVERSE_SPEED     100 // 0 is stopped, 400 is full speed
#define TURN_SPEED        100
#define FORWARD_SPEED     100
#define REVERSE_DURATION  100 // ms
#define TURN_DURATION     200 // ms

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

//ZumoBuzzer buzzer;
//ZumoMotors motors;
//Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 300;
/*
void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
   
  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);  
  delay(1000);
}
*/

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

void setup() 
{
  //pinMode(LED, HIGH);
   
  //waitForButtonAndCountDown();
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("waiting...");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  if (Serial.available()>0) 
  {
    char movement = (char) Serial.read();    
    switch (movement)
    {
      case 'w': motors.setSpeeds(400, 400); break;
      case 'd': motors.setSpeeds(400, -400); break;
      case 's': motors.setSpeeds(-400, -400);  break;
      case 'a': motors.setSpeeds(-400, 400); break;
      case ' ': motors.setSpeeds(0,0); break;
      case 'task2':
      {
 /*
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }
   */

  sensors.read(sensor_values);
  
  if (sensor_values[0] > QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensor_values[5] > QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else
  {
    // otherwise, go straight
    motors.setSpeeds(0, 200);
  }
}
      }
    } // end switch
  } // end if something read on Serial...


