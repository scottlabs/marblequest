/*
  Fade.cpp - The class definition for a fade animation.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Fade.h"
Fade::Fade(int _x, int _y, int _width, int _height, double _speed, boolean _repeat, double _temp, boolean _temp_up)
{
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  temp = _temp;
  temp_up = _temp_up;
  speed = _speed;
  repeat = _repeat;
}

Fade::Fade(int _x, int _y, int _width, int _height, double _speed)
{
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  temp = 1;
  temp_up = false;
  speed = _speed;
  repeat = true;
}


void Fade::draw(double* matrix, int rows, int cols)
{
  
   for (int i=x;i<x+width;i++) {
     for (int j=y;j<y+height;j++) {
       setPixel(matrix,i,j,temp);
     }
  }
  
  
  changeTemperature();



}

void Fade::changeTemperature() {
  if (temp >= 1 && repeat) {
    temp_up = false;
  } else if (temp <= 0 && repeat) {
    temp_up = true;    
  }
  
  //double temp_scale = 0.01;
  
  if (temp_up==true) {
    temp += speed;  
  } else if (temp_up==false) {
    temp -= speed;
  }
   
}
