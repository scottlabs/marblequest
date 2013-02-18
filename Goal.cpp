/*
  Goal.cpp - The class definition for a goal character.
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Goal.h"
#include "Fade.h"

Goal::Goal() : Fade(0,0,0+2,0+2,0.07) {}
Goal::Goal(int _x, int _y) : Fade(_x,_y,_x+2,_y+2,0.07) {
  
}
/*

Goal::Goal(int _x, int _y, int _width, int _height, double _speed) {

}
Goal::Goal(int _x, int _y)
{
  x = _x;
  y = _y;
  width = 2;
  height = 2;
  //super(x,y,width,height,0.1);  

}

*/
