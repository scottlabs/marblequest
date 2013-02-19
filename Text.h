/*
  Text.h - The class definition for a Text object
  Created by Kevin Scott, February 18, 2013
  Released into the public domain.
*/
#ifndef Text_h
#define Text_h

#include "Arduino.h"
#include "Actor.h"

class Text : public Actor
{
  public:
    Text(unsigned int _letter);
    virtual void draw(double* matrix,int _x,int _y);
    void destroy();
    double x;
    double y;
  private:
    unsigned int letter;
    double value;

};
#endif
