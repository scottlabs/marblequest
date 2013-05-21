/*
  Board.cpp - The class definition for our board.
  
  This class is responsible for a majority of the game. 
  
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
 
 
 */

#include "Arduino.h"
#include "Board.h"
#include "Marble.h"

#include "Goal.h"
#include "Block.h"
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
  
  // define the size of our matrix.
  level_width = cols + 16;
  level_height = rows + 16;
  populated = false;

  level_state = 0;
  auto_calibrate = true;
  playing = false;
  
  marble = Marble(-1,-1);

  level_one(); // create level one.
}

// This method handles drawing the actual game board.
// It does this by calling the draw methods on each
// of its children.
boolean Board::draw(double* matrix) {
  if (millis() - level_time > level_wait) {
    if (level_state==1 && populated==false) {
      populated = true;
      level_one_populate(); 
    }
  }
  
  for (int i=0;i<rows*cols;i++) {
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

  // if we're not outside our wait period, don't go.
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
  
  // handle collisions
  boolean x_collision = false;
  boolean y_collision = false;  
  unsigned int j =0;
  
  
  double marble_x = marble.x-x-move_x;
  double marble_y = marble.y-y-move_y;
  
  // detect whether the goal has been reached.
  if (goal.collides(marble,x,y)) {
    complete_level();
  }
  
  // detect whether there are any collisions between the marble and the walls.
  while(j<children.size() && (x_collision==false || y_collision==false) ) {
    if (x_collision == false) { 
      x_collision = marble.collides(marble_x,children[j]->getX(),marble.y-y,children[j]->getY()); 
    }
    if (y_collision == false) {     
      y_collision = marble.collides(marble_y,children[j]->getY(),marble.x-x,children[j]->getX()); 
    }    
    j++; 
  }
  

  // determine amount to move board, and don't exceed certain amounts.
  if (x+move_x < 0-(level_width - 8) ) { move_x = 0; }
  if (x+move_x > 0 ) { move_x = 0; }

  if (y+move_y < 0-(level_height - 8)) { move_y = 0; }
  if (y+move_y > 0) { move_y = 0; }
  
  // if there are no collisions, move the board.
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
}

// A method, called once a level is complete. Determines
// your score and how many hearts you get.

void Board::complete_level() {
  auto_calibrate = false;
  children.clear();
  playing = false;
  marble = Marble(-1,-1);
  unsigned int hearts;
  unsigned int total_level_time = millis() - level_wait;

  if (total_level_time < 4000) {  
    hearts = 7;    
  } else if (total_level_time < 5000) {  
    hearts = 6;
  } else if (total_level_time < 6000) {
    hearts = 5;
  } else if (total_level_time < 7000) {
    hearts = 4;
  } else if (total_level_time < 12000) {
    hearts = 3;
  } else if (total_level_time < 20000) {
    hearts = 2;
  } else {
    hearts = 1;
  }
  
  hearts = 2;
  goal.heart(hearts); // Turn our goal object into a heart.
  
}

// A method that sets up the scaffolding and intro screen for level one.
void Board::level_one() {
  populated = false;
  children.push_back(new Text(1));
  level_wait = 3600;
  level_time = millis();
  level_state = 1;
  
}

// A method that specifies the particular positions of each Block in our level.
void Board::level_one_populate() {
  children.clear();
  start_time = millis();
  playing = true;
  marble = Marble(3,3);
  goal = Goal(10,10);
  children.push_back(new Block(2,2));
  children.push_back(new Block(2,3));
  children.push_back(new Block(2,4));
  children.push_back(new Block(2,5));
  children.push_back(new Block(2,6));
  children.push_back(new Block(2,7));
  children.push_back(new Block(3,2));
  children.push_back(new Block(3,7));
  children.push_back(new Block(4,2));
  children.push_back(new Block(4,7));
  children.push_back(new Block(5,2));
  children.push_back(new Block(5,7));
  children.push_back(new Block(6,2));
  children.push_back(new Block(6,3));
  children.push_back(new Block(6,6));
  children.push_back(new Block(6,7));
  children.push_back(new Block(7,2));
  children.push_back(new Block(7,7));
  children.push_back(new Block(8,2));
  children.push_back(new Block(8,7));
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
