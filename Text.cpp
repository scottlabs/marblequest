/*
  Text.cpp - The class definition for a Text object
  
  Hardcoded definitions for various bits of text
  
  Created by Kevin Scott, February 18, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Text.h"

Text::Text(unsigned int _letter)
{
  letter = _letter;
  value = 1;
  x = 0;
  y = 0;
}
// This is far from ideal; to destroy a bit of text just kick it off the page.
void Text::destroy() {
  x += -9;
  y += -9;
}
// Specific hardcoded definitions of Text characters.
void Text::draw(double* matrix,int _x,int _y) {
  if (letter==1) {
    setPixel(matrix,x+7,y+4,value);
    setPixel(matrix,x+6,y+2,value);
    setPixel(matrix,x+6,y+3,value);
    setPixel(matrix,x+6,y+4,value);
    setPixel(matrix,x+5,y+4,value);
    setPixel(matrix,x+4,y+4,value);
    setPixel(matrix,x+3,y+4,value);
    setPixel(matrix,x+2,y+4,value);
    setPixel(matrix,x+1,y+2,value);
    setPixel(matrix,x+1,y+3,value);
    setPixel(matrix,x+1,y+4,value);
    setPixel(matrix,x+1,y+5,value);
    setPixel(matrix,x+1,y+6,value);
  } else if (letter==2) {
    setPixel(matrix,x+7,y+3,value);  
    setPixel(matrix,x+7,y+4,value);
    setPixel(matrix,x+6,y+2,value);
    setPixel(matrix,x+6,y+5,value);
    setPixel(matrix,x+5,y+5,value);
    setPixel(matrix,x+4,y+4,value);
    setPixel(matrix,x+3,y+3,value);
    setPixel(matrix,x+2,y+2,value);
    setPixel(matrix,x+1,y+2,value);
    setPixel(matrix,x+1,y+3,value);
    setPixel(matrix,x+1,y+4,value);
    setPixel(matrix,x+1,y+5,value);
  } else if (letter==3) {
    setPixel(matrix,x+7,y+3,value);
    setPixel(matrix,x+7,y+4,value);
    setPixel(matrix,x+6,y+2,value);
    setPixel(matrix,x+6,y+5,value);
    setPixel(matrix,x+5,y+5,value);
    setPixel(matrix,x+4,y+4,value);
    setPixel(matrix,x+4,y+5,value);
    setPixel(matrix,x+3,y+5,value);
    setPixel(matrix,x+2,y+2,value);
    setPixel(matrix,x+2,y+5,value);
    setPixel(matrix,x+1,y+3,value);
    setPixel(matrix,x+1,y+4,value); 
  }
}



