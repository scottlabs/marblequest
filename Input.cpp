/*
  Input.cpp - The class definition for our input device (accelerometer)
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
  //int zpin = A2;
  pinMode(sleepPin,OUTPUT);
  digitalWrite(sleepPin, HIGH);//turns off sleep mode and activates device
  
  pinMode(xpin, INPUT);//input mode
  digitalWrite(xpin, HIGH);//turn on pull up resistor
  
  pinMode(ypin, INPUT);//input mode
  digitalWrite(ypin, HIGH);//turn on pull up resistor

   //Minx: 312 Miny: 334 Maxx: 704 Maxy: 645

  // Minx: 574 Miny: 622 Maxx: 672 Maxy: 716

 //Minx: 591 Miny: 571 Maxx: 739 Maxy: 739

// Minx: 537 Miny: 619 Maxx: 682 Maxy: 717
//585 Miny: 603 Maxx: 744 Maxy: 752
    minx = 585;
    miny = 600;
    maxx = 744;
    maxy = 755;
   avg_x = 0;
   avg_y = 0;
  
  smoothing = 3;
  calibrated = false;

  Point point;
}

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
    

    //Serial.println(" ");
    Serial.print("Y"); 

    Serial.println(analogRead(ypin));


    delay(50);
  }
}

Point Input::getPoint() {
   if (point.x > 1) { point.x = 1; }
   if (point.x < -1) { point.x = -1; }
   if (point.y > 1) { point.y = 1; }
   if (point.y < -1) { point.y = -1; }
   return point; 
}

float Input::parseReading(float val, float min, float max) {
  //Serial.println("reading: ");
  //Serial.println(val);
  val = val-min;
  val = val/(max-min);
  //Serial.println(val);
  
  return (val-0.5)*2;
}

Point Input::val()
{
  //Point point;
  //delay(100); //Delay for readability
  //Serial.println(parseReading(analogRead(xpin)));
  
  
  
  boolean acceler = true;
  if (acceler) {
    avg_x = ((avg_x * (smoothing-1)) + analogRead(xpin))/smoothing;
  
    avg_y = ((avg_y * (smoothing-1)) + analogRead(ypin))/smoothing;
    //Serial.println("x");
    double x_reading = parseReading(avg_x, minx, maxx);
    //Serial.println("y");  
    double y_reading = parseReading(avg_y, miny, maxy);  
    //return point;
    
    // lets do some nudging on our values to get them flat.
    x_reading *= -1.58; 
    x_reading -= 1.15;
    

    y_reading *= 1.55;
    y_reading += 0.97;    

    
    //if (x_reading > 0) { x_reading *= 1.8 ; }
    //if (x_reading < 0) { x_reading *= 1.4; }

    // right now, y = 1.10 to -1.48
    // x = 1.9 to -0.85
    
    y_reading *= 1;
    x_reading *= -1;  
    
    point.x = x_reading;
    point.y = y_reading;
    
    boolean autoset_calibration = true;
    if (autoset_calibration) {
      if (avg_x > maxx && avg_x < 900) { maxx = avg_x; }
      if (avg_x < minx && avg_x > 250) { minx = avg_x; }
      if (avg_y > maxy && avg_x < 900) { maxy = avg_y; }
      if (avg_y < miny && avg_y > 250) { miny = avg_y; }
      
    }
    
  
    boolean debug = false;
    if (debug) {
      Serial.print(" Analog X: ");
      Serial.print(analogRead(xpin));
      Serial.print(" Analog Y: ");
      Serial.print(analogRead(ypin));    
      Serial.print(" X:");
  
      Serial.print(point.x);
      
  
      //Serial.println(" ");
      Serial.print(" Y:"); 
  
      Serial.print(point.y);
  
      Serial.println(" "); 
      delay(50);
      //readCalibration();   
    }
  } else {
     point.x = analogRead(xpin)/512 - 1;
     point.y = analogRead(ypin)/512 - 1;
  }
  
  return getPoint();

}
