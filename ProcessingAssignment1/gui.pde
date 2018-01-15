/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void button1_click1(GButton source, GEvent event) { //_CODE_:btnRight:481471:
  println("btnRight - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("d");
} //_CODE_:btnRight:481471:

public void button2_click1(GButton source, GEvent event) { //_CODE_:btnUp:317093:
  println("btnUp - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("w");
} //_CODE_:btnUp:317093:

public void button3_click1(GButton source, GEvent event) { //_CODE_:btnLeft:956673:
  println("btnLeft - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("a");
} //_CODE_:btnLeft:956673:

public void button4_click1(GButton source, GEvent event) { //_CODE_:btnDown:987894:
  println("btnDown - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("s");
} //_CODE_:btnDown:987894:

public void button1_click2(GButton source, GEvent event) { //_CODE_:btnStop:632732:
  println("btnStop - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("o");
} //_CODE_:btnStop:632732:

public void button1_click3(GButton source, GEvent event) { //_CODE_:btnObjectsFound:442839:
  println("btntask2 - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("f");
} //_CODE_:btnObjectsFound:442839:

public void textarea1_change1(GTextArea source, GEvent event) { //_CODE_:txtAreaMessage:713942:
  println("txtAreaMessage - GTextArea >> GEvent." + event + " @ " + millis());
  //String text = myPort.readStringuntil();
  //txtAreaMessage.setText(text);
  //txtAreaMessage.
} //_CODE_:txtAreaMessage:713942:

public void button2_click2(GButton source, GEvent event) { //_CODE_:btnscanRoom:664862:
  println("btnscanRoom - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("r");
} //_CODE_:btnscanRoom:664862:

public void button1_click4(GButton source, GEvent event) { //_CODE_:btncomplete:898717:
  println("button1 - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("c");
} //_CODE_:btncomplete:898717:

public void button2_click3(GButton source, GEvent event) { //_CODE_:btnrightRoom:814781:
  println("btnrightRoom - GButton >> GEvent." + event + " @ " + millis());
  myPort.write(">");
} //_CODE_:btnrightRoom:814781:

public void button3_click2(GButton source, GEvent event) { //_CODE_:btnleftRoom:713857:
  println("btnleftRoom - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("<");
} //_CODE_:btnleftRoom:713857:

public void button1_click5(GButton source, GEvent event) { //_CODE_:btnLeftCorridor:243522:
  println("btnLeftCorridor - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("z");
} //_CODE_:btnLeftCorridor:243522:

public void button1_click6(GButton source, GEvent event) { //_CODE_:btnRightCorridor:451312:
  println("btnRightCorridor - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("x");
} //_CODE_:btnRightCorridor:451312:

public void button1_click7(GButton source, GEvent event) { //_CODE_:btnClearText:787071:
  println("btnClearText - GButton >> GEvent." + event + " @ " + millis());
  txtAreaMessage.setText("");
} //_CODE_:btnClearText:787071:

public void button1_click8(GButton source, GEvent event) { //_CODE_:btnEnd:487189:
  println("btnEnd - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("t");
  txtAreaMessage.setText("");
} //_CODE_:btnEnd:487189:

public void button1_click9(GButton source, GEvent event) { //_CODE_:btnCorridor:736791:
  println("btnCorridor - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("m");
} //_CODE_:btnCorridor:736791:

public void button1_click10(GButton source, GEvent event) { //_CODE_:btnLeftPlus:792935:
  println("btnLeftPlus - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("b");
} //_CODE_:btnLeftPlus:792935:

public void button2_click4(GButton source, GEvent event) { //_CODE_:btnRightPlus:702919:
  println("btnRightPlus - GButton >> GEvent." + event + " @ " + millis());
  myPort.write("n");
} //_CODE_:btnRightPlus:702919:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  surface.setTitle("Sketch Window");
  btnRight = new GButton(this, 188, 78, 80, 30);
  btnRight.setText("RIGHT");
  btnRight.setTextBold();
  btnRight.addEventHandler(this, "button1_click1");
  btnUp = new GButton(this, 98, 64, 80, 30);
  btnUp.setText("UP");
  btnUp.setTextBold();
  btnUp.addEventHandler(this, "button2_click1");
  btnLeft = new GButton(this, 8, 78, 80, 30);
  btnLeft.setText("LEFT");
  btnLeft.setTextBold();
  btnLeft.addEventHandler(this, "button3_click1");
  btnDown = new GButton(this, 94, 148, 80, 30);
  btnDown.setText("DOWN");
  btnDown.setTextBold();
  btnDown.addEventHandler(this, "button4_click1");
  btnStop = new GButton(this, 96, 106, 80, 30);
  btnStop.setText("STOP");
  btnStop.setTextBold();
  btnStop.setLocalColorScheme(GCScheme.RED_SCHEME);
  btnStop.addEventHandler(this, "button1_click2");
  btnObjectsFound = new GButton(this, 489, 212, 80, 30);
  btnObjectsFound.setText("OBJECTS");
  btnObjectsFound.setTextBold();
  btnObjectsFound.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  btnObjectsFound.addEventHandler(this, "button1_click3");
  txtAreaMessage = new GTextArea(this, 10, 216, 447, 150, G4P.SCROLLBARS_BOTH);
  txtAreaMessage.setOpaque(true);
  txtAreaMessage.addEventHandler(this, "textarea1_change1");
  btnscanRoom = new GButton(this, 490, 262, 80, 30);
  btnscanRoom.setText("SCAN ROOM");
  btnscanRoom.setTextBold();
  btnscanRoom.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  btnscanRoom.addEventHandler(this, "button2_click2");
  btncomplete = new GButton(this, 411, 60, 80, 30);
  btncomplete.setText("COMPLETE");
  btncomplete.setTextBold();
  btncomplete.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  btncomplete.addEventHandler(this, "button1_click4");
  btnrightRoom = new GButton(this, 500, 101, 84, 36);
  btnrightRoom.setText("RIGHT ROOM");
  btnrightRoom.setTextBold();
  btnrightRoom.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnrightRoom.addEventHandler(this, "button2_click3");
  btnleftRoom = new GButton(this, 319, 102, 80, 34);
  btnleftRoom.setText("LEFT ROOM");
  btnleftRoom.setTextBold();
  btnleftRoom.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btnleftRoom.addEventHandler(this, "button3_click2");
  label1 = new GLabel(this, -4, 37, 171, 20);
  label1.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label1.setText("WASD CONTROLS");
  label1.setTextBold();
  label1.setTextItalic();
  label1.setLocalColorScheme(GCScheme.SCHEME_11);
  label1.setOpaque(false);
  label2 = new GLabel(this, 318, 36, 248, 20);
  label2.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label2.setText("ROOM AND CORRIDOR BUTTONS");
  label2.setTextBold();
  label2.setTextItalic();
  label2.setLocalColorScheme(GCScheme.SCHEME_13);
  label2.setOpaque(false);
  btnLeftCorridor = new GButton(this, 317, 145, 79, 41);
  btnLeftCorridor.setText("LEFT CORRIDOR");
  btnLeftCorridor.setTextBold();
  btnLeftCorridor.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  btnLeftCorridor.addEventHandler(this, "button1_click5");
  btnRightCorridor = new GButton(this, 498, 144, 84, 39);
  btnRightCorridor.setText("RIGHT CORRIDOR");
  btnRightCorridor.setTextBold();
  btnRightCorridor.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  btnRightCorridor.addEventHandler(this, "button1_click6");
  btnClearText = new GButton(this, 358, 374, 100, 22);
  btnClearText.setText("CLEAR TEXT");
  btnClearText.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  btnClearText.addEventHandler(this, "button1_click7");
  btnEnd = new GButton(this, 425, 105, 52, 62);
  btnEnd.setText("END");
  btnEnd.setTextBold();
  btnEnd.setLocalColorScheme(GCScheme.RED_SCHEME);
  btnEnd.addEventHandler(this, "button1_click8");
  label3 = new GLabel(this, 140, 7, 221, 20);
  label3.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label3.setText("FIND AND RESCUE MISSION");
  label3.setTextBold();
  label3.setTextItalic();
  label3.setLocalColorScheme(GCScheme.SCHEME_10);
  label3.setOpaque(false);
  label4 = new GLabel(this, 0, 187, 173, 20);
  label4.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label4.setText("TEXT AREA MESSAGES");
  label4.setLocalColorScheme(GCScheme.SCHEME_13);
  label4.setOpaque(false);
  btnCorridor = new GButton(this, 490, 310, 80, 30);
  btnCorridor.setText("CORRIDOR");
  btnCorridor.setTextBold();
  btnCorridor.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  btnCorridor.addEventHandler(this, "button1_click9");
  btnLeftPlus = new GButton(this, 6, 122, 80, 30);
  btnLeftPlus.setText("LEFT+");
  btnLeftPlus.setTextBold();
  btnLeftPlus.addEventHandler(this, "button1_click10");
  btnRightPlus = new GButton(this, 187, 123, 80, 30);
  btnRightPlus.setText("RIGHT+");
  btnRightPlus.setTextBold();
  btnRightPlus.addEventHandler(this, "button2_click4");
}

// Variable declarations 
// autogenerated do not edit
GButton btnRight; 
GButton btnUp; 
GButton btnLeft; 
GButton btnDown; 
GButton btnStop; 
GButton btnObjectsFound; 
GTextArea txtAreaMessage; 
GButton btnscanRoom; 
GButton btncomplete; 
GButton btnrightRoom; 
GButton btnleftRoom; 
GLabel label1; 
GLabel label2; 
GButton btnLeftCorridor; 
GButton btnRightCorridor; 
GButton btnClearText; 
GButton btnEnd; 
GLabel label3; 
GLabel label4; 
GButton btnCorridor; 
GButton btnLeftPlus; 
GButton btnRightPlus; 