/*
  Fade.cpp - The class definition for a fade animation.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Fade.h"

Fade::Fade(int _x, int _y, int _width, int _height, double _speed)
{
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  temp = 1;
  temp_up = false;
  speed = _speed;
}


void Fade::draw(double* matrix, int rows, int cols)
{
  // heart
  if (0) {
      
      
    setPixel(matrix,1,1,temp);
    setPixel(matrix,2,1,temp);
    setPixel(matrix,5,1,temp);
    setPixel(matrix,6,1,temp);
    for (int i=0;i<8;i++) {
      setPixel(matrix,i,2,temp);
      setPixel(matrix,i,3,temp);
    }
    for (int i=1;i<7;i++) {
      setPixel(matrix,i,4,temp);
    }
    for (int i=2;i<6;i++) {
      setPixel(matrix,i,5,temp);
    }  
    for (int i=3;i<5;i++) {
      setPixel(matrix,i,6,temp);
    } 
  }  else {
   
   for (int i=x;i<x+width;i++) {
     for (int j=y;j<y+height;j++) {
       setPixel(matrix,i,j,temp);
     }
   } 
  }
    changeTemperature();



}

void Fade::changeTemperature() {
  if (temp >= 1) {
    temp_up = false;
  } else if (temp <= 0) {
    temp_up = true;    
  }
  
  //double temp_scale = 0.01;
  
  if (temp_up==true) {
    temp += speed;  
  } else if (temp_up==false) {
    temp -= speed;
  }
   
}
