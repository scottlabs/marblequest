/*
  Text.cpp - The class definition for a Text object
  Created by Kevin Scott, February 18, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Text.h"

Text::Text(unsigned int _letter)
{
  letter = _letter;
  value = 1;
}

void Text::draw(double* matrix,int _x,int _y) {
  if (letter==1) {
setPixel(matrix,7,4,value);
setPixel(matrix,6,2,value);
setPixel(matrix,6,3,value);
setPixel(matrix,6,4,value);
setPixel(matrix,5,4,value);
setPixel(matrix,4,4,value);
setPixel(matrix,3,4,value);
setPixel(matrix,2,4,value);
setPixel(matrix,1,2,value);
setPixel(matrix,1,3,value);
setPixel(matrix,1,4,value);
setPixel(matrix,1,5,value);
setPixel(matrix,1,6,value);
  } else if (letter==2) {
      setPixel(matrix,7,3,value);
setPixel(matrix,7,4,value);
setPixel(matrix,6,2,value);
setPixel(matrix,6,5,value);
setPixel(matrix,5,5,value);
setPixel(matrix,4,4,value);
setPixel(matrix,3,3,value);
setPixel(matrix,2,2,value);
setPixel(matrix,1,2,value);
setPixel(matrix,1,3,value);
setPixel(matrix,1,4,value);
setPixel(matrix,1,5,value);
  } else if (letter==3) {
    setPixel(matrix,7,3,value);
setPixel(matrix,7,4,value);
setPixel(matrix,6,2,value);
setPixel(matrix,6,5,value);
setPixel(matrix,5,5,value);
setPixel(matrix,4,4,value);
setPixel(matrix,4,5,value);
setPixel(matrix,3,5,value);
setPixel(matrix,2,2,value);
setPixel(matrix,2,5,value);
setPixel(matrix,1,3,value);
setPixel(matrix,1,4,value); 
  }
}



