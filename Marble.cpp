/*
  Marble.cpp - The class definition for our marble character.
  
  
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Marble.h"

// Our constructors.
Marble::Marble() {}
Marble::Marble(int _x, int _y)
{
  x = _x;
  y = _y;
  value = 1;
}

// The drawing method, simply sets the correct pixels.
void Marble::draw(double* matrix, int _x, int _y) 
{
   setPixel(matrix,round(x) + _x,round(y) + _y,value);
}

// The collision method. Detects whether the marble has made contact with any Blocks (walls)
boolean Marble::collides(double val, double target_val, double static_val, double static_target_val) {
  int rounded_val = round(val);
  int rounded_target_val = round(target_val);
  int rounded_static_val = round(static_val);
  int rounded_static_target_val = round(static_target_val);
  
  // if the location values match, report a collision
  if (rounded_val == rounded_target_val && rounded_static_val == rounded_static_target_val) {
    return true; 
  }
  return false;  
  
}
