/*
  Fade.h - The class definition for a goal character.
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/
#ifndef Goal_h
#define Goal_h

#include "Arduino.h"
#include "Fade.h"
#include "Actor.h"


class Goal : public Fade {
  public:
    Goal();
    Goal(int _x, int _y);
  private:

};
#endif
