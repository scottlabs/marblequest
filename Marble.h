/*
  Marble.h - The class definition for our marble character.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/
#ifndef Marble_h
#define Marble_h

#include "Arduino.h"
#include "Actor.h"
#include "Block.h"

class Marble : public Actor {
  public:
    Marble();
    Marble(int _x, int _y);

    virtual void draw(double* matrix,int _x, int _y);
    virtual void move(double _x, double _y);
    //y_collision = marble.collides(y+move_y,children[j]->getY());        
    boolean collides(double val, double target_val, double static_val, double static_target_val);
    
    double x;
    double y;
  private:
};
#endif
