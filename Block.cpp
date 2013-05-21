/*
  Block.cpp - The class definition for a block object. 
  
  A block is a single pixel wall. A marble cannot go through a block (but 
  that logic resides in the logic).
  
  Created by Kevin Scott, February 17, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Block.h"

Block::Block(){}

Block::Block(int _x, int _y)
{
  x = _x;
  y = _y;
  value = 0.5; // the brightness of the walls
}

// draws the actual block onto the board
void Block::draw(double* matrix,int _x,int _y) {
  setPixel(matrix,x+_x,y+_y,value);  
}
int Block::getX(){ return x; }
int Block::getY(){ return y; }
