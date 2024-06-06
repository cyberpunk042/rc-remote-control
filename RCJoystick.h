// RCJoystick.h
#ifndef RCJOYSTICK_H
#define RCJOYSTICK_H

/*
  Hardware:
  - 2-axis joystick
  - pushbuttons
*/

class RCJoystick {
private:
    int mouseButton;
    int xAxis;
    int yAxis;

public:
    RCJoystick(int xA, int yA, int button) : mouseButton(button), xAxis(xA), yAxis(yA), range(10), threshold(2), center(5) {}

    // parameters for reading the joystick:
    int range;             // output range of X or Y movement
    int threshold; // range / 4;  // resting threshold
    int center; // range / 2;     // resting position value

    void setup() {
      pinMode(xAxis, INPUT);
      pinMode(yAxis, INPUT);
      pinMode(mouseButton, INPUT);
    }

    String read() {
      // read and scale the two axes:
      int xReading = readAxis(xAxis);
      int yReading = readAxis(yAxis);

      // if the mouse button is pressed:
      if (digitalRead(mouseButton) == HIGH) {
        // Add any action to perform when the button is pressed
      }

      return String(xReading) + "," + String(yReading);
      // delay(responseDelay);
    }

    /*
      reads an axis (0 or 1 for x or y) and scales the analog input range to a range
      from 0 to <range>
    */
    int readAxis(int thisAxis) {
      // read the analog input:
      int reading = analogRead(thisAxis);

      // map the reading from the analog input range to the output range:
      reading = map(reading, 0, 1023, 0, range);

      // if the output reading is outside from the rest position threshold, use it:
      int distance = reading - center;

      if (abs(distance) < threshold) {
        distance = 0;
      }

      // return the distance for this axis:
      return distance;
    }
};

#endif
