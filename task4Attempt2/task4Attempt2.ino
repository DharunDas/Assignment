#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <NewPing.h>

#define LED 13
//#define QTR_THRESHOLD 1500 // microseconds




ZumoMotors motors;
ZumoBuzzer buzzer;
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
#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() 
{
  // Play a little welcome song
  buzzer.play(">g32>>c32");
  
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
  buzzer.play(">g32>>c32");
  button.waitForButton();
  //buzzer.play("L16 cdegreg4");
  //while(buzzer.isPlaying());
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
      case 'w': motors.setSpeeds(150, 150);
      borderDetect = true;
      break;
      case 'd': motors.setSpeeds(200, -200);
      delay(200);
      motors.setSpeeds(0,0);
      //borderDetect = false;
      break;
      case 's': motors.setSpeeds(-200, -200);
      //borderDetect = false;
      break;
      case 'a': motors.setSpeeds(-200, 200);
      delay(200);
      motors.setSpeeds(0,0);
      //borderDetect = false;
      break;
      case 'o': motors.setSpeeds(0,0);
      borderDetect = false;
      break;
      case 'r':
      Serial.println("Room Mode.");

        Serial.println("\nTurn robot and wait");

        delay(1000);

        //roomTurn();
        scanRoom();
        //mode = 4;

        break;
      
    } // end switch
  } // end if something read on Serial...
  reflectanceSensors.read(sensor_values);


//STOP PROGRAM LOOP
if (borderDetect == true){
  
  if((sensor_values[2]) && (sensor_values[3]) >= reflectanceSensors.calibratedMaximumOn[2])
  {
    Serial.write("A Wall Has Been Detected!  \f");
     motors.setSpeeds(0, 0);
    //delay(REVERSE_DURATION);
    //motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    //delay(TURN_DURATION);
   // motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  /*else if(sensor_values[5] >= reflectanceSensors.calibratedMaximumOn[5])
  {
    Serial.write("A Wall Has Been Detected!  \f");
     motors.setSpeeds(0, 0);
    //delay(REVERSE_DURATION);
    //motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    //delay(TURN_DURATION);
   // motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }*/
  else if((sensor_values[0]) && (sensor_values[1]) >= reflectanceSensors.calibratedMaximumOn[1])
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if((sensor_values[4]) && (sensor_values[5]) >= reflectanceSensors.calibratedMaximumOn[4])
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
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
void scanRoom() {

  bool found = false;

  Serial.print("\nRoom scanning started.");

  //Automatically start the motors to go forward.

  motors.setSpeeds(100, 100);

  delay(600);

  motors.setSpeeds(0,0);



  delay(1000);



  //Start the Zumo turning right.

  motors.setSpeeds(200, -200);

  delay(800);

  motors.setSpeeds(0,0);

  delay(200);



  //Start the Zumo turning left and starts scanning.

  motors.setSpeeds(-200, 200); 

  //delay(1750);

  for(int i=0; i<35; i++) {

    if(sonar.ping_cm() <= 30 && sonar.ping_cm() > 0)

      buzzer.play(">g32>>c32");
    //If an item has been found in the CM radius bool is set to true.

      found = true;

    delay(50);
  }
  
  motors.setSpeeds(0,0);

  delay(200);



  //Start Zumo turning right and scanning initiated.

  motors.setSpeeds(200, -200); 

  //delay(2000);

  for(int i=0; i<40; i++) {

    if(sonar.ping_cm() <= 30 && sonar.ping_cm() > 0)

      found = true;

    delay(50);
  }
  
  Serial.print(".");

  motors.setSpeeds(0,0);

  delay(200);

  Serial.print(".");

  

  motors.setSpeeds(-200, 200); // turn left

  delay(800);

  motors.setSpeeds(0,0);

  Serial.println("Complete");

  

  /*if(found) {

    if(mode != 6)

      Serial.println("Object has been found");

    else

      Serial.println("OBJECT STILL IN ROOM");

  }

  else {

    if(mode != 6)

      Serial.println("No object found.");

    else

      Serial.println("ROOM CLEARED");

  }



  if(mode != 6){

    path[path_length].item = found;

    path_length++;

    

    Serial.println("Please move Zumo back into corridor.");

    Serial.println("Press 'c' when complete.");

    mode = 1;

  }  */
  
}


