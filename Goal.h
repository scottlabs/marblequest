/*
  Fade.h - The class definition for a goal character.
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/
#ifndef Goal_h
#define Goal_h

#include "Arduino.h"
#include "Actor.h"
#include "Marble.h"


class Goal : public Actor {
  public:
    int x;
    int y;
    Goal();
    Goal(int _x, int _y);
    virtual void draw(double* matrix, int _x, int _y);
    boolean collides(Marble marble, double board_x, double board_y);
    void heart();
  private:
    int width;
    int height;
    int threshold;
    boolean temp_up;
    double temp;
    double speed;
    void changeTemperature();
    unsigned int time;
    int state;
    void drawBox(double* matrix, int _x, int _y);
    void drawHeart(double* matrix, int _x, int _y);



};
#endif
