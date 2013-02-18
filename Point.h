/*
  Point.h - The class definition for an x,y point.
  Created by Kevin Scott, February 11, 2013
  Released into the public domain.
*/
#ifndef Point_h
#define Point_h

#include "Arduino.h"

class Point
{
  public:
    Point();
    Point(float _x, float _y);    
    double x;
    double y;
    virtual double getX();
    virtual double gety();    
};
#endif
