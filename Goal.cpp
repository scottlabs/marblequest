/*
  Goal.cpp - The class definition for a goal character.
  Created by Kevin Scott, February 15, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Goal.h"

Goal::Goal(){}

Goal::Goal(int _x, int _y){
  //fade(0,0,8,8,0.1);
  
  x = _x;
  y = _y;

  height = 2;
  width = 2;
  
  threshold = 1;
  // actual height and widt
  height -= 1;
  width -= 1;
  
  temp = 1;
  state = 0; // 0 is regular draw
  time = 0;
  
  temp_up = false;
  //grow_step = 0;
  
  speed = 0.07;
  //go_heart = false;
  //heart_count = 0;
  heart_begin = 0;
  hearts = 0;
}
boolean Goal::collides(Marble marble, double board_x, double board_y) {
  int marble_x = round(marble.x - board_x);
  int marble_y = round(marble.y - board_y);  
  if (marble_x >= x && marble_x <= x+width && marble_y >= y && marble_y <= y+height) {
    return true;
  }
  return false;
}
void Goal::heart(unsigned int _hearts) {
  state = 1; // 1 is heart
  //speed = 0.2;
  hearts = _hearts;
  time = millis();
}


void Goal::drawBox(double* matrix, int _x, int _y) {
  setPixel(matrix,round(x) + _x,round(y) + _y,temp);
  setPixel(matrix,round(x) + _x + width,round(y) + _y,temp);
  setPixel(matrix,round(x) + _x,round(y) + _y + height,temp);
  setPixel(matrix,round(x) + _x + width,round(y) + _y + height,temp);

}

void Goal::drawHeart(double* matrix, int _x, int _y) {
  if (heart_begin==0) { heart_begin = millis(); }
  //int goal_x = round(x) + _x; // this is the 0,0 part of the goal  
  //int goal_y = round(y) + _y; // this is the 0,0 part of the goal
  //drawBox(matrix,_x,_y);

  unsigned int heart_length = 840;
  if (millis() - heart_begin < hearts * heart_length) { // should be 5
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
void Goal::draw(double* matrix, int _x, int _y) {
  if (state==0) {
    drawBox(matrix, _x, _y);
  } else if (state==1) {
    drawHeart(matrix, _x, _y);
  }
  
  /*
  if (go_heart == false) {
    
  } else if (go_heart == true) {
    
  }
  */
  changeTemperature();
}

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
