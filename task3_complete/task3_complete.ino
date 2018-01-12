#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#define LED 13
//#define QTR_THRESHOLD 1500 // microseconds




ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray reflectanceSensors;
bool borderDetect =false;
// This is the maximum speed the motors will be allowed to turn.
// (400 lets the motors go at top speed; decrease to impose a speed limit)
const int MAX_SPEED = 300;

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("waiting...");
  delay(500);
  reflectanceSensors.init();
  
    // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  button.waitForButton();
  
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);
    // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  button.waitForButton();
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
      case 'w': motors.setSpeeds(200, 200);
      borderDetect = true;
      break;
      case 'd': motors.setSpeeds(230, -230);
      delay(360);
      motors.setSpeeds(0,0);
      //borderDetect = false;
      break;
      case 's': motors.setSpeeds(-400, -400);
      //borderDetect = false;
      break;
      case 'a': motors.setSpeeds(-230, 230);
      delay(360);
      motors.setSpeeds(0,0);
      //borderDetect = false;
      break;
      case 'o': motors.setSpeeds(0,0);
      borderDetect = false;
      break;
      //case 't':
      
    } // end switch
  } // end if something read on Serial...
  reflectanceSensors.read(sensor_values);


//STOP PROGRAM LOOP
if (borderDetect == true){
  
  if(sensor_values[0] >= reflectanceSensors.calibratedMaximumOn[0])
  {
    Serial.write("A Wall Has Been Detected!  \f");
     motors.setSpeeds(0, 0);
    //delay(REVERSE_DURATION);
    //motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    //delay(TURN_DURATION);
   // motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if(sensor_values[5] >= reflectanceSensors.calibratedMaximumOn[5])
  {
    Serial.write("A Wall Has Been Detected!  \f");
     motors.setSpeeds(0, 0);
    //delay(REVERSE_DURATION);
    //motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    //delay(TURN_DURATION);
   // motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  /*else if((sensor_values[1] >= reflectanceSensors.calibratedMaximumOn[1])&&(sensor_values[2] >= reflectanceSensors.calibratedMaximumOn[2]) && (sensor_values[3] >= reflectanceSensors.calibratedMaximumOn[3])&&(sensor_values[4] >= reflectanceSensors.calibratedMaximumOn[4]))
  {
    motors.setSpeeds(0,0);
  }*/
  /*else
  {
    motors.setSpeeds(200, 200);
  }*/
}
  
}


