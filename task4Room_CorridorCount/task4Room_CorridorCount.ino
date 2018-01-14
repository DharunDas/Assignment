#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <NewPing.h>

#define LED 13

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

//int room_no;
char dir;
char movement;
int corridor_count =0;
int turn_count_l =0;
int turn_count_r = 0;

//int room_count = 1;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() 
{
  // Play a little welcome song
  buzzer.play(">g32>>c32");
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("waiting...");
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
      motors.setSpeeds(-240, 240);
    else
      motors.setSpeeds(240, -240);
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

void roomTurn() 

{

  turn_count_l = 0;

  turn_count_r = 0;

}

void loop() 
{
  // put your main code here, to run repeatedly:
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  if (Serial.available()>0) 
  {
    
    movement = Serial.read();    
    switch (movement)
    {
      case 'w': motors.setSpeeds(150, 150);
      //borderDetect = true;
      break;
      case 'd': motors.setSpeeds(200, -200);
      delay(200);
      motors.setSpeeds(0,0);
      break;
      case 's': motors.setSpeeds(-200, -200);
      break;
      case 'a': motors.setSpeeds(-200, 200);
      delay(200);
      motors.setSpeeds(0,0);
      break;
      case 'o': motors.setSpeeds(0,0);
      break;
      case 'c': motors.setSpeeds(150, 150);
      break;
      /*case 'r':
      Serial.print("Room Mode. \f");
        //Serial.print("\nTurn robot and wait");
        delay(1000);
        //roomTurn();
        scanRoom();
        //mode = 4;
        break;*/
        case '<': 
        //turn_count_l++;
        motors.setSpeeds(-200,200);
        delay(450);
        motors.setSpeeds(0,0);
        scanLeftRoom();
        break;
        case '>': 
        //digitalWrite(13, HIGH);
        //turn_count_r++;
        motors.setSpeeds(200,-200);
        delay(450);
        motors.setSpeeds(0,0);
        scanRightRoom();
        break;
        case 'z': 
        corridor_count++;
        Serial.println("This is corridor "+ (String)corridor_count + " \f");
        // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
        break;
        case 'x': 
        corridor_count++;
        Serial.println("This is corridor "+ (String)corridor_count + " \f");
        motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
        break;
      
    } // end switch
  } // end if something read on Serial...
  reflectanceSensors.read(sensor_values);
   
  if(sensor_values[2] >= reflectanceSensors.calibratedMaximumOn[2] && sensor_values[3] >= reflectanceSensors.calibratedMaximumOn[3])
  {
    Serial.println("A Wall Has Been Detected \f");
    motors.setSpeeds(-120, -120);
    delay(150);  
     motors.setSpeeds(0, 0);  
  }
 
  else if((sensor_values[0]) && (sensor_values[1]) >= reflectanceSensors.calibratedMaximumOn[1])
  {Serial.print("Left border Been Detected!  \f");
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if((sensor_values[4]) && (sensor_values[5]) >= reflectanceSensors.calibratedMaximumOn[4])
  {Serial.print("Right border Been Detected!  \f");
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}
/*void scanRoom() {

  //Serial.print("\nRoom " + (String)turn_count_r + "\f");
  Serial.print("\nRoom scanning started. \f");
  bool found = false;
  
  if (movement = '>')
  {
    turn_count_r++;
    //digitalWrite(13, HIGH);
    Serial.print("This is room number " + (String)turn_count_r + " on the right hand side of the corridor \f");
  }
  else if (movement = '<')
  {
    turn_count_l++;
    digitalWrite(13, HIGH);
    Serial.print("This is room number " + (String)turn_count_l+ " on the left hand side of the corridor \f");
  }
  else{
    
    Serial.print("Complete");
  }

  //Automatically start the motors to go forward.
  motors.setSpeeds(100, 100);
  delay(600);
  motors.setSpeeds(0,0);
  delay(1000);
  //Start the Zumo turning right.
  motors.setSpeeds(100, -100);
  delay(800);
  motors.setSpeeds(0,0);
  delay(200);
  //Start the Zumo turning left and starts scanning.
  motors.setSpeeds(-100, 100); 
  //delay(1750);
  for(int i=0; i<35; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      buzzer.play(">g32>>c32");
    //If an item has been found in the CM radius bool is set to true.
      found = true;
    delay(50);
  }  
  motors.setSpeeds(0,0);
  delay(200);
  //Start Zumo turning right and scanning initiated.
  motors.setSpeeds(100, -100); 
  //delay(2000);
  for(int i=0; i<40; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      found = true;
    delay(50);
  }  
  Serial.print(".");
  motors.setSpeeds(0,0);
  delay(200);
  Serial.print(".");
  motors.setSpeeds(-100, 100); // turn left
  delay(800);
  motors.setSpeeds(0,0);
}*/

void scanLeftRoom() {

  //Serial.print("\nRoom " + (String)turn_count_r + "\f");
  Serial.print("\nLeft Room scanning started. \f");
  bool found = false;
  
  if (movement = '<')
  {
    turn_count_l++;
    digitalWrite(13, HIGH);
    Serial.print("This is room number " + (String)turn_count_l+ " on the left hand side of the corridor \f");
  }
  else{
    
    Serial.print("Complete");
  }

  //Automatically start the motors to go forward.
  motors.setSpeeds(100, 100);
  delay(600);
  motors.setSpeeds(0,0);
  delay(1000);
  //Start the Zumo turning right.
  motors.setSpeeds(100, -100);
  delay(800);
  motors.setSpeeds(0,0);
  delay(200);
  //Start the Zumo turning left and starts scanning.
  motors.setSpeeds(-100, 100); 
  //delay(1750);
  for(int i=0; i<35; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      buzzer.play(">g32>>c32");
    //If an item has been found in the CM radius bool is set to true.
      found = true;
    delay(50);
  }  
  motors.setSpeeds(0,0);
  delay(200);
  //Start Zumo turning right and scanning initiated.
  motors.setSpeeds(100, -100); 
  //delay(2000);
  for(int i=0; i<40; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      found = true;
    delay(50);
  }  
  Serial.print(".");
  motors.setSpeeds(0,0);
  delay(200);
  Serial.print(".");
  motors.setSpeeds(-100, 100); // turn left
  delay(800);
  motors.setSpeeds(0,0);
}

void scanRightRoom() {

  //Serial.print("\nRoom " + (String)turn_count_r + "\f");
  Serial.print("\nRoom scanning started. \f");
  bool found = false;
  
  if (movement = '>')
  {
    turn_count_r++;
    //digitalWrite(13, HIGH);
    Serial.print("This is room number " + (String)turn_count_r + " on the right hand side of the corridor \f");
  }
  else{
    
    Serial.print("Complete");
  }

  //Automatically start the motors to go forward.
  motors.setSpeeds(100, 100);
  delay(600);
  motors.setSpeeds(0,0);
  delay(1000);
  //Start the Zumo turning right.
  motors.setSpeeds(100, -100);
  delay(800);
  motors.setSpeeds(0,0);
  delay(200);
  //Start the Zumo turning left and starts scanning.
  motors.setSpeeds(-100, 100); 
  //delay(1750);
  for(int i=0; i<35; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      buzzer.play(">g32>>c32");
    //If an item has been found in the CM radius bool is set to true.
      found = true;
    delay(50);
  }  
  motors.setSpeeds(0,0);
  delay(200);
  //Start Zumo turning right and scanning initiated.
  motors.setSpeeds(100, -100); 
  //delay(2000);
  for(int i=0; i<40; i++) {
    if(sonar.ping_cm() <= 20 && sonar.ping_cm() > 0)
      found = true;
    delay(50);
  }  
  Serial.print(".");
  motors.setSpeeds(0,0);
  delay(200);
  Serial.print(".");
  motors.setSpeeds(-100, 100); // turn left
  delay(800);
  motors.setSpeeds(0,0);
}

