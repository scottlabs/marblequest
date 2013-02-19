/*
  Marble.cpp - The class definition for our marble character.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Marble.h"

Marble::Marble() {}

Marble::Marble(int _x, int _y)
{
  x = _x;
  y = _y;
  
  value = 1;
}


void Marble::draw(double* matrix, int _x, int _y) 
{
  //Serial.println(" draw ");
  if (0) {
    
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);  
  Serial.print(" x: ");
  Serial.print((round(x) + _x));
  Serial.print(" y: ");
  Serial.println((round(y) + _y));  
  }
  // matrix[9] = 1;
   setPixel(matrix,round(x) + _x,round(y) + _y,value);
   //Serial.println("marble draw");
}

void Marble::move(double _x, double _y) {


  
  x += _x;
  y += _y; 
  /*
  if (x < 1) { x = 1; }
  if (y < 1) { y = 1; }
  if (x > 6) { x = 6; }
  if (y > 6) { y = 6; } 
 */ 
}


boolean Marble::collides(double val, double target_val, double static_val, double static_target_val) {
  //Serial.print(point->x);
  int rounded_val = round(val);
  int rounded_target_val = round(target_val);
  int rounded_static_val = round(static_val);
  int rounded_static_target_val = round(static_target_val);
  
  boolean debug = false;
  if (rounded_val == rounded_target_val && rounded_static_val == rounded_static_target_val) {
    if (debug) {
      Serial.print("check val: ");
      //Serial.println(check_val);
      Serial.print("point val: ");
      //Serial.println(check_point_val);
      delay(50);
    }

    return true; 
  }
  return false;  
  
}
