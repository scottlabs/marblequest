/*
  Board.cpp - The class definition for our board.
 Created by Kevin Scott, February 10, 2013
 Released into the public domain.
 */

#include "Arduino.h"
#include "Board.h"
#include "Marble.h"

#include "Goal.h"
#include "Block.h"
#include "Fade.h"
#include "Text.h"

#include <math.h>



#include <iterator>
#include <vector>
Marble marble;
//Goal goal;
Goal goal;

Board::Board()
{
  x = 0;
  y = 0;
  
  start_time = millis();
  wait = 400;
  
  cols = 8;
  rows = 8;
  
  level_width = cols + 16;
  level_height = rows + 16;
  populated = false;

  level_state = 0;
  auto_calibrate = true;
  playing = false;
  //Marble *marble = new Marble(); // new returns a pointer.
//  Wall *wall = new Wall(0,0,0,1);
  
  marble = Marble(-1,-1);

  level_one();
}


boolean Board::draw(double* matrix) {
  //int rows_cols = rows*cols;
  //double board_matrix[rows_cols];
  
  
  if (millis() - level_time > level_wait) {
    if (level_state==1 && populated==false) {
      populated = true;
      level_one_populate(); 
    }
  }
  
  
  for (int i=0;i<rows*cols;i++) {
    //board_matrix[i] = 0;
    matrix[i] = 0;
        
  }
  int rounded_x = round(x);
  int rounded_y = round(y);
  marble.draw(matrix,0,0);
  goal.draw(matrix,rounded_x,rounded_y);
  
  for (unsigned int j=0;j<children.size();j++) {
    children[j]->draw(matrix,rounded_x,rounded_y);
  }

  return auto_calibrate; // auto calibrate our board, or don't.
}


// Move the board by a specified amount,
// as specified by x and y
void Board::move(double move_x, double move_y)
{
  if (playing == false) { return; }

  
  if (millis() - start_time < wait) {
    return; 
  }  
  double threshold = 1.1;
  
  if (move_x > threshold) {
    move_x = 0;
  } else if (move_x < 0-threshold) {
     move_x = 0; 
  }
  if (move_y > threshold) {
    move_y = 0;
  } else if (move_y < 0-threshold) {

     move_y = 0; 
  }  

  
  //return;
  //Marble *m = children[0];
  //children[0]->move(-1*move_x,-1*move_y);    
  //return; 


  
  //Serial.println("MOVE");
  //for (int j=0;j<children.size();j++) {
    
    
  boolean x_collision = false;
  boolean y_collision = false;  
  unsigned int j =0;
  boolean debug = false;  

  
  double marble_x = marble.x-x-move_x;
  double marble_y = marble.y-y-move_y;
  
  if (goal.collides(marble,x,y)) {
    
    complete_level();
     //children[0] = new Fade(0,0,20,20,0.1);
  }
  
  
  while(j<children.size() && (x_collision==false || y_collision==false) ) {

    if (x_collision == false) { 
      x_collision = marble.collides(marble_x,children[j]->getX(),marble.y-y,children[j]->getY()); 
      if (debug && x_collision == true) {
        Serial.println("x collision");
        Serial.print("point x and y: ");
        Serial.print(children[j]->getX());
        Serial.print(" ");
        Serial.println(children[j]->getY());
      }
    }
    if (y_collision == false) { 
    
      y_collision = marble.collides(marble_y,children[j]->getY(),marble.x-x,children[j]->getX()); 
      if (debug && y_collision == true) {
        Serial.println("y collision");
        Serial.print("point x and y: ");
        Serial.print(children[j]->getX());
        Serial.print(" ");
        Serial.println(children[j]->getY());
      }
    }
    
    j++; 
  }
  
  
  

  if (x+move_x < 0-(level_width - 8) ) { move_x = 0; }
  if (x+move_x > 0 ) { move_x = 0; }

  if (y+move_y < 0-(level_height - 8)) { move_y = 0; }
  if (y+move_y > 0) { move_y = 0; }
  
  
  boolean allow_marble_to_move = false;
  if (x_collision==false) {
    if (allow_marble_to_move) {
      

      if (marble.x+move_x < 4 || marble.x +move_x > 3) {
        marble.x += move_x;
      } else {
        x += move_x;  
      }
    } else {
      x += move_x;  
    }
  }
  if (y_collision==false) {  
    if (allow_marble_to_move) {    
  
      if (marble.y+move_y < 4 || marble.y +move_y > 3) {
        marble.y += move_y;
      } else {
        y += move_y;
      }
    } else {    
      y += move_y;    
    }
  }
  boolean debug2 = false;
  if (debug2) {
    
    Serial.print(" x collide: " );
    Serial.print(x_collision);
    Serial.print(" y collide: " );
    Serial.print(y_collision);  
    Serial.print(" x: " );
    Serial.print(move_x);
    Serial.print(" y: " );
    Serial.print(move_y);  
    Serial.println(" ");
    delay(50);
  }

    
}

void Board::complete_level() {
  auto_calibrate = false;
  children.clear();
  playing = false;
  marble = Marble(-1,-1);
  goal.heart();

}
void Board::level_one() {
  
  populated = false;
  //children.push_back(new Text(1));
  //children.clear();
  level_wait = 01;
  level_time = millis();
  level_state = 1;
}
void Board::level_one_populate() {
  children.clear();
  start_time = millis();
  playing = true;
  marble = Marble(3,3);

  goal = Goal(8,10);
  //goal = Goal(3,3);
  children.push_back(new Block(2,2));
  children.push_back(new Block(2,3));
  children.push_back(new Block(2,4));
  children.push_back(new Block(2,5));
  children.push_back(new Block(2,6));
  children.push_back(new Block(2,7));
  children.push_back(new Block(2,8));
  children.push_back(new Block(3,2));
  children.push_back(new Block(3,8));
  children.push_back(new Block(4,2));
  children.push_back(new Block(4,8));
  children.push_back(new Block(5,2));
  children.push_back(new Block(5,8));
  children.push_back(new Block(6,2));
  children.push_back(new Block(6,3));
  children.push_back(new Block(6,4));
  children.push_back(new Block(6,6));
  children.push_back(new Block(6,7));
  children.push_back(new Block(6,8));
  children.push_back(new Block(7,2));
  children.push_back(new Block(7,8));
  children.push_back(new Block(8,2));
  children.push_back(new Block(8,8));
  children.push_back(new Block(8,9));
  children.push_back(new Block(8,10));
  children.push_back(new Block(8,11));
  children.push_back(new Block(8,12));
  children.push_back(new Block(8,13));
  children.push_back(new Block(9,2));
  children.push_back(new Block(9,4));
  children.push_back(new Block(9,5));
  children.push_back(new Block(9,6));
  children.push_back(new Block(9,7));
  children.push_back(new Block(9,8));
  children.push_back(new Block(9,13));
  children.push_back(new Block(10,2));
  children.push_back(new Block(10,8));
  children.push_back(new Block(10,13));
  children.push_back(new Block(11,2));
  children.push_back(new Block(11,5));
  children.push_back(new Block(11,8));
  children.push_back(new Block(11,13));
  children.push_back(new Block(12,2));
  children.push_back(new Block(12,5));
  children.push_back(new Block(12,13));
  children.push_back(new Block(13,2));
  children.push_back(new Block(13,3));
  children.push_back(new Block(13,4));
  children.push_back(new Block(13,5));
  children.push_back(new Block(13,6));
  children.push_back(new Block(13,7));
  children.push_back(new Block(13,8));
  children.push_back(new Block(13,9));
  children.push_back(new Block(13,10));
  children.push_back(new Block(13,11));
  children.push_back(new Block(13,12));
  children.push_back(new Block(13,13));
}
