/*
  Input.cpp - The class definition for our input device (accelerometer)
  
  Is responsible for reading the input and also translating it into a floating 
  value between -1 and 1.
  
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Input.h"

Input::Input()
{
  sleepPin= 1; //Turning sleep high turns on the Accelerometer
  xpin= A4;
  ypin = A5;

  pinMode(sleepPin,OUTPUT);
  digitalWrite(sleepPin, HIGH);//turns off sleep mode and activates device
  
  pinMode(xpin, INPUT);//input mode
  digitalWrite(xpin, HIGH);//turn on pull up resistor
  
  pinMode(ypin, INPUT);//input mode
  digitalWrite(ypin, HIGH);//turn on pull up resistor

  // these are our calibrated values. The input device does not generally exceed 
  // these values.
  minx = 585;
  miny = 600;
  maxx = 744;
  maxy = 755;
  
  // we smooth our input over time to reduce noisy readings.
  avg_x = 0;
  avg_y = 0;
  smoothing = 3;
  
  calibrated = false;

  Point point;
}

// This method returns a Point object representing the Accelerometer state.
// It also checks that all values are sane, and if not, corrects them to be
// within the expected range.
Point Input::getPoint() {
   if (point.x > 1) { point.x = 1; }
   if (point.x < -1) { point.x = -1; }
   if (point.y > 1) { point.y = 1; }
   if (point.y < -1) { point.y = -1; }
   return point; 
}

// Translate our value from a large integer into a float between -1 and 1.
float Input::parseReading(float val, float min, float max) {
  val = val-min;
  val = val/(max-min);
  return (val-0.5)*2;
}

// This method returns the current value of the Accelerometer.
Point Input::val()
{
  // Our value gets smoothed so as to reduce noisiness in the signal.
  avg_x = ((avg_x * (smoothing-1)) + analogRead(xpin))/smoothing;
  avg_y = ((avg_y * (smoothing-1)) + analogRead(ypin))/smoothing;
  
  // And is then readjusted to be between -1 and 1.
  double x_reading = parseReading(avg_x, minx, maxx);
  double y_reading = parseReading(avg_y, miny, maxy);  
  
  // Whoops! We're still not done. Despite our calibration, the input values are
  // off. Some trial and error produced the following calculations that gets them
  // where we need them.
  x_reading *= -1.58; 
  x_reading -= 1.15;
  y_reading *= 1.55;
  y_reading += 0.97;    
  
  // x points in the opposite direction; reverse it.
  x_reading *= -1; 
  
  point.x = x_reading;
  point.y = y_reading;
  
  // this will check the input values against our calibrated settings, and if necessary,
  // recalibrate on the fly. This generally should not be necessary but is included as
  // a precaution, if anything changes in the hardware.
  boolean autoset_calibration = true;
  if (autoset_calibration) {
    if (avg_x > maxx && avg_x < 900) { maxx = avg_x; }
    if (avg_x < minx && avg_x > 250) { minx = avg_x; }
    if (avg_y > maxy && avg_x < 900) { maxy = avg_y; }
    if (avg_y < miny && avg_y > 250) { miny = avg_y; }
    
  }  
  return getPoint();
}





// These two methods are used to calibrate the device.
void Input::calibrate()
{
  
  if (calibrated == false) {
    minx = 9999;
    miny = 9999;
    maxx = 0;
    maxy = 0;
    calibrated = true;
  }
    
  int xreading = analogRead(xpin);
  int yreading = analogRead(ypin);
  
  if (minx > xreading) { minx = xreading; }
  if (miny > yreading) { miny = yreading; }  
  if (maxx < xreading) { maxx = xreading; }
  if (maxy < yreading) { maxy = yreading; } 

  readCalibration();
}

void Input::readCalibration() {
  if (0) {
    Serial.print(" Analog X: ");
    Serial.print(analogRead(xpin));
    Serial.print(" Analog Y: ");
    Serial.print(analogRead(ypin));
    Serial.print(" Minx: "); 
    Serial.print(minx);
    Serial.print(" Miny: "); 
    Serial.print(miny);
    Serial.print(" Maxx: "); 
    Serial.print(maxx);
    Serial.print(" Maxy: "); 
    Serial.print(maxy);  
    Serial.println("");
    delay(50);
  } else {
    Serial.print("X");
    Serial.println(analogRead(xpin));
    Serial.print("Y"); 
    Serial.println(analogRead(ypin));
    delay(50);
  }
}
