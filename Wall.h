/*
  Wall.h - The class definition for a wall object.
  Created by Kevin Scott, February 11, 2013
  Released into the public domain.
*/
#ifndef Wall_h
#define Wall_h

#include "Arduino.h"
#include "Point.h"
#include "Actor.h"

class Wall : public Actor
{
  public:
    Wall();
    Wall(int start_x, int start_y, int end_x, int end_y);

    virtual void draw(double* matrix,int _x,int _y);
    //virtual boolean onScreen(double _x, double _y);
    double slope;
    double b;
    double length;
    double angle;
    Point start;
    Point end;
};
#endif
