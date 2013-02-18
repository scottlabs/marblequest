/*
  Block.cpp - The class definition for a block object.
  Created by Kevin Scott, February 17, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Block.h"



Block::Block()
{

}

Block::Block(int _x, int _y)
{
  x = _x;
  y = _y;
  value = 0.5; // the brightness of the walls
  //value = 1;
}

void Block::draw(double* matrix,int _x,int _y) {
  setPixel(matrix,x+_x,y+_y,value);  
}

boolean Block::collision(double _x, double _y) {
  
}
