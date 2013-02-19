/*
  Actor.cpp - Our base class definition that our characters and objects extend from
  Created by Kevin Scott, February 13, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Actor.h"

Actor::Actor()
{
  value = 1;
}

void Actor::setPixel(double* matrix, int x,int y,double val) {
  int cols = 8;
  int matrix_index = y+(x*cols);
  if (0) {
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);  
  }
  if (x >= 0 && x < 8 && y >= 0 && y < 8 && matrix_index >= 0 && matrix_index <= 63 && val > matrix[matrix_index]) {
    matrix[y+(x*cols)] = val;  
  }
  
}

boolean Actor::onScreen(double _x, double _y) {
  return true; 
}
void Actor::draw(double* matrix, int x, int y) {
}

void Actor::move(double _x, double _y){
  //Serial.println("actor move");
}

int Actor::getX(){ return 0; }
int Actor::getY(){ return 0; }
