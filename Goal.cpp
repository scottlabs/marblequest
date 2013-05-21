/*
  Goal.cpp - The class definition for a goal character.
  
  A Goal object serves two functions. It is both the object the Marble must collide with
  (this signifying the level is complete) and is also responsible for displaying the user's
  score via throbbing a heart a certain number of times, to indicate the level score.
  
  The Goal object is also responsible for detecting collision with the Marble, as the Marble
  collision detection is only designed to deal with single pixel objects, like blocks.
  
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Goal.h"

Goal::Goal(){}

Goal::Goal(int _x, int _y){
  
  x = _x;
  y = _y;

  // these actually mean its 2x2
  height = 1;
  width = 1;
  
  temp = 1; // our starting value
  state = 0; // 0 is a regular Goal object.
  time = 0;
  temp_up = false;
  speed = 0.07;
  heart_begin = 0;
  hearts = 0;
}

// This method detects the collision between the Marble object and the Goal.
// This resides here as the Marble collision function is designed to only deal with
// single pixel objects, and the Goal object is multi pixel.
boolean Goal::collides(Marble marble, double board_x, double board_y) {
  int marble_x = round(marble.x - board_x);
  int marble_y = round(marble.y - board_y);  
  if (marble_x >= x && marble_x <= x+width && marble_y >= y && marble_y <= y+height) {
    return true;
  }
  return false;
}

// This method flips the Goal object into a Heart object.
void Goal::heart(unsigned int _hearts) {
  state = 1; // 1 is heart
  hearts = _hearts;
  time = millis();
}

// This method draws a box, representing a Goal object in a level. It is a 2x2 box that throbs.
void Goal::drawBox(double* matrix, int _x, int _y) {
  setPixel(matrix,round(x) + _x,round(y) + _y,temp);
  setPixel(matrix,round(x) + _x + width,round(y) + _y,temp);
  setPixel(matrix,round(x) + _x,round(y) + _y + height,temp);
  setPixel(matrix,round(x) + _x + width,round(y) + _y + height,temp);
}

// This method that is responsible for drawing a heart a specified number
// of times. When a user completes the level, it will display a certain number of
// hearts depending on their time.
//
// This specifies which pixels to light up. 
void Goal::drawHeart(double* matrix, int _x, int _y) {
  if (heart_begin==0) { heart_begin = millis(); }

  unsigned int heart_length = 860;
  if (millis() - heart_begin < hearts * heart_length) {
    setPixel(matrix,6,1,temp);
    setPixel(matrix,6,2,temp);    
    setPixel(matrix,6,5,temp);    
    setPixel(matrix,6,6,temp);        
    
    for (int i=0;i<8;i++) {
      setPixel(matrix,5,i,temp);
      setPixel(matrix,4,i,temp);
    }
    for (int i=1;i<7;i++) {
      setPixel(matrix,3,i,temp);
    }
    for (int i=2;i<6;i++) {
      setPixel(matrix,2,i,temp);
    }  
    for (int i=3;i<5;i++) {
      setPixel(matrix,1,i,temp);
    }
  }
  
}

// Responsible for drawing a goal object; also will convert the Goal
// object into heart images at the end of the game.
void Goal::draw(double* matrix, int _x, int _y) {
  if (state==0) {
    drawBox(matrix, _x, _y);
  } else if (state==1) {
    drawHeart(matrix, _x, _y);
  }
  changeTemperature();
}

// Ramp our value up and down by flipping a boolean when the value hits
// 0 or 1. Then increment the value by some amount.
void Goal::changeTemperature() {
  if (temp >= 1) {
    temp_up = false;
  } else if (temp <= 0) {
    temp_up = true;    
  }

  if (temp_up==true) {
    temp += speed;  
  } else if (temp_up==false) {
    temp -= speed;
  }
}
