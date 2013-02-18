/*
  Input.h - The class definition for our input device (accelerometer)
  Created by Kevin Scott, February 11, 2013
  Released into the public domain.
*/
#ifndef Input_h
#define Input_h

#include "Arduino.h"
#include "Point.h"

class Input
{
  public:
    Input();
    Point val();
    void calibrate();
    Point getPoint();
  private:
    void readCalibration();
    float parseReading(float val, float min, float max);
    int minx;
    int miny;
    int maxx;
    int maxy;
    int sleepPin;
    int xpin;
    int ypin;
    
    double avg_x;
    double avg_y;
    int smoothing;
    Point point;
    
    boolean calibrated;
};
#endif
