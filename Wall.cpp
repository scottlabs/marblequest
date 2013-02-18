/*
  Wall.cpp - The class definition for a wall object.
  Created by Kevin Scott, February 11, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "Wall.h"



Wall::Wall()
{

}

Wall::Wall(int start_x, int start_y, int end_x, int end_y)
{
  start = Point(start_x, start_y);
  end = Point(end_x, end_y);  
  slope = ((end.y-start.y) / (end.x-start.x));
  
  b = start.y - (slope*start.x);
  
  
  length = sqrt((pow((end.x-start.x),2)) + (pow((end.y-start.y),2)) );

  
  //param = 1.0;
  angle = atan (slope);

  //printf ("The arc tangent of %lf is %lf degrees\n", param, result );
  
  value = 0.5; // the brightness of the walls
  value = 1;
}

void Wall::draw(double* matrix,int _x,int _y) {
  /*
  Serial.print("I am wall: ");
  Serial.print(start.x);
  Serial.print(", ");  
  Serial.print(start.y);
  Serial.print(", ");  
  Serial.print(end.x);
  Serial.print(", ");  
  Serial.print(end.y);
  Serial.print(", ");  
  Serial.print(length);
  Serial.print(", ");  
  Serial.print(slope);
  Serial.println(""); 
*/  
  /*
  double x_pow = pow((end.x-start.x),2);
  double y_pow = pow((end.y-start.y),2);  
  Serial.print("pows: ");
  Serial.println(x_pow);
  Serial.println(y_pow);  
  

  Serial.print("length: ");
  Serial.println(length);
  */
  //setPixel(matrix,start.x,start.y,temp);
  for (int i=0;i<length;i++) {
    // cos (angle) = x / i;
    int x = floor(cos(angle) * i) + start.x;
    int y = floor(sin(angle) * i) + start.y;    
    //x = 0;
    
    //int x = i;
    //int y = round(slope*x + b);
    //int x = arcsin(O/i);

    setPixel(matrix,x+_x,y+_y,value);
  }
  
  
  //setPixel(matrix,0,0,0.5);
}

boolean Wall::onScreen(double _x, double _y) {
}
