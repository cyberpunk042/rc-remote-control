#include "RCJoystick.h"
#include "RFTransmitter.h"

RCJoystick leftJoystick(A0, A1, 6); 
RCJoystick rightJoystick(A2, A3, 5); 
RFTransmitter transmitter(7, 8); 

void setup() {
  Serial.begin(9600);
  leftJoystick.setup();
  rightJoystick.setup();
  transmitter.setup();
}

void loop() {
  String readingLeft = leftJoystick.read();
  String readingRight = rightJoystick.read();
  String command = "L:" + getYValue(readingLeft) + ",R:" + getYValue(readingRight);
  //Serial.println(command);
  transmitter.loop(command);
  delay(100);
}

String getYValue(String data) {
  int commaIndex = data.indexOf(',');
  return data.substring(commaIndex + 1);
}