/*
  Point.cpp - The class definition for an x,y point.
  
  Basically just abstracts away a coordinate point.
  
  Created by Kevin Scott, February 11, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Point.h"

Point::Point(){}
Point::Point(float _x, float _y)
{
  x = _x;
  y = _y;
}
double Point::getX() {
  return x;
}
double Point::gety() {
  return y;
}
