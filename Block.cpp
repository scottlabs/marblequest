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
  value = 0.7; // the brightness of the walls
  //value = 1;
}

void Block::draw(double* matrix,int _x,int _y) {
  setPixel(matrix,x+_x,y+_y,value);  
}
int Block::getX(){ return x; }
int Block::getY(){ return y; }
