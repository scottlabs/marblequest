/*
  Fade.h - The class definition for a fade animation.
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/
#ifndef Fade_h
#define Fade_h

#include "Arduino.h"
#include "Actor.h"

class Fade : public Actor {
  public:
    Fade(int _x, int _y, int _width, int _height, double _speed);
    Fade(int _x, int _y, int _width, int _height, double _speed, boolean _repeat, double _temp, boolean _temp_up);
    virtual void draw(double* matrix, int rows, int cols);
  private:
    boolean repeat;
    int x;
    int y;
    int width;
    int height;
    double temp;
    boolean temp_up;
    void changeTemperature();
    double speed;

};
#endif
