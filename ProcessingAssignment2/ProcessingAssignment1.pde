// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port



public void setup(){
  size(600, 500, JAVA2D);
  createGUI();
  customGUI();
  myPort = new Serial(this, "COM4", 9600);
  // Place your setup code here
  
  
}

public void draw(){
  background(230);
  message();
  
  
}

public void message(){
  if (myPort.available()>0){
  String text = myPort.readStringUntil('\f');
  //txtAreaMessage.setText("\n");
  txtAreaMessage.setText(text);
  
  }
}

/*public void message(){
  
  String text = myPort.readStringUntil('z');
  txtAreaMessage.setText(text);
}*/

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

}