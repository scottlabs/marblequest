/*
  Block.h - The class definition for a block object.
  Created by Kevin Scott, February 17, 2013
  Released into the public domain.
*/
#ifndef Block_h
#define Block_h

#include "Arduino.h"
#include "Actor.h"

class Block : public Actor
{
  public:
    Block();
    Block(int _x, int _y);
    int x;
    int y;
    virtual void draw(double* matrix,int _x,int _y);
    virtual boolean collision(double _x, double _y);    
};
#endif
