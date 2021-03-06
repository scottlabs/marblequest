/*
  Actor.h - Our base class definition that our characters and objects extend from
  Created by Kevin Scott, February 13, 2013
  Released into the public domain.
*/
#ifndef Actor_h
#define Actor_h

#include "Arduino.h"

class Actor
{
  public:
    Actor();
    virtual void draw(double* matrix, int x, int y);
    void setPixel(double* matrix, int x,int y,double val);

    double value;
    
    virtual int getX();
    virtual int getY();    
  private:

};
#endif
