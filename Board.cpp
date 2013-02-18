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
#include <math.h>



#include <iterator>
#include <vector>
Marble marble;
//Goal goal;
//Board::Board(double* _matrix, int _cols, int _rows)
Board::Board()
{
  x = 0;
  y = 0;
  
  start_time = millis();
  wait = 400;
  
  cols = 8;
  rows = 8;
  
  level_width = cols + 10;
  level_height = rows + 10;



  //Marble *marble = new Marble(); // new returns a pointer.
//  Wall *wall = new Wall(0,0,0,1);
  
//  Goal *goal = new Goal(2,2);
  marble = Marble(3,3);
  //goal = Goal(4,10  );  
  
  //Marble *m = new Marble(4,4);  
  if (1) {

    //children.push_back(new Marble(0,0));   
    //children.push_back(new Marble(2,2));       
    //children.push_back(new Marble(4,4));   
    //children.push_back(new Marble(6,6));       
    //children.push_back(new Marble(8,8));           
  
children.push_back(new Block(2,2));
children.push_back(new Block(3,2));
children.push_back(new Block(4,2));
children.push_back(new Block(5,2));
children.push_back(new Block(6,2));
children.push_back(new Block(7,2));
children.push_back(new Block(8,2));
children.push_back(new Block(9,2));
children.push_back(new Block(10,2));
children.push_back(new Block(11,2));
children.push_back(new Block(12,2));
children.push_back(new Block(13,2));
children.push_back(new Block(2,3));
children.push_back(new Block(8,3));
children.push_back(new Block(13,3));
children.push_back(new Block(2,4));
children.push_back(new Block(8,4));
children.push_back(new Block(13,4));
children.push_back(new Block(2,5));
children.push_back(new Block(8,5));
children.push_back(new Block(13,5));
children.push_back(new Block(2,6));
children.push_back(new Block(8,6));
children.push_back(new Block(13,6));
children.push_back(new Block(2,7));
children.push_back(new Block(13,7));
children.push_back(new Block(2,8));
children.push_back(new Block(3,8));
children.push_back(new Block(4,8));
children.push_back(new Block(5,8));
children.push_back(new Block(6,8));
children.push_back(new Block(7,8));
children.push_back(new Block(8,8));
children.push_back(new Block(9,8));
children.push_back(new Block(10,8));
children.push_back(new Block(11,8));
children.push_back(new Block(13,8));
children.push_back(new Block(2,9));
children.push_back(new Block(13,9));
children.push_back(new Block(2,10));
children.push_back(new Block(13,10));
children.push_back(new Block(2,11));
children.push_back(new Block(13,11));
children.push_back(new Block(2,12));
children.push_back(new Block(13,12));
children.push_back(new Block(2,13));
children.push_back(new Block(3,13));
children.push_back(new Block(4,13));
children.push_back(new Block(5,13));
children.push_back(new Block(6,13));
children.push_back(new Block(7,13));
children.push_back(new Block(8,13));
children.push_back(new Block(9,13));
children.push_back(new Block(10,13));
children.push_back(new Block(11,13));
children.push_back(new Block(12,13));
children.push_back(new Block(13,13));  

    
    
    //children.push_back(new Wall(3,3,3,12));
    /*
    children.push_back(new Wall(2,2,10,2));
    children.push_back(new Wall(3,2,3,10));
 
    children.push_back(new Wall(9,2,10,10));
    //children.push_back(new Wall(2,2,10,0));

    children.push_back(new Wall(2,9,8,10));
    */
  
  //
  } else{
    children.push_back(new Fade(0,0,8,8,0.1));     // 6 is the endpoint, not the width / height
  }
  
  
  
  //children.push_back(new Wall(0,8,0,0));   
  
  
  /*
  children.push_back(new Wall(0,0,0,0));  
  children.push_back(new Wall(1,0,1,1));    
  children.push_back(new Wall(2,0,2,2));
  children.push_back(new Wall(3,0,3,3));  
  children.push_back(new Wall(4,0,4,4));  
  children.push_back(new Wall(5,0,5,5));  
  children.push_back(new Wall(6,0,6,6));  
  children.push_back(new Wall(7,0,7,7));  
  */
  
  //x = 2;
  //y = 2;
  
}


boolean Board::draw(double* matrix) {
  int rows_cols = rows*cols;
  //double board_matrix[rows_cols];
  
  for (int i=0;i<rows*cols;i++) {
    //board_matrix[i] = 0;
    matrix[i] = 0;
        
  }
  int rounded_x = round(x);
  int rounded_y = round(y);
  marble.draw(matrix,0,0);
  for (int j=0;j<children.size();j++) {
  //for (int j=0;j<3;j++) {
    children[j]->draw(matrix,rounded_x,rounded_y);

  }

  
  if (0) {
    
    Serial.print(" x: " );
    Serial.print(rounded_x);
    Serial.print(" y: " );
    Serial.print(rounded_y);  
    Serial.println(" ");
    delay(100);
  }
  

  
  //rounded_y = 1;
  
  /*
  for (int i=0;i<8;i++) {
    for (int j=0;j<8;j++) {    
      int matrix_index = (i*8)+j;
      //int board_matrix_index = matrix_index;
      //int board_matrix_index = matrix_index + rounded_x + ((cols-8) * i) + (rounded_y * cols);
      //int board_matrix_index = (i*8) + j + (rounded_y * 8) + rounded_x + (i);
      boolean debug = false;
      if (debug) {
        Serial.print("Board matrix index: ");
        //Serial.print(board_matrix_index);
        Serial.print(" | i: ");
        Serial.print(i);
        Serial.print(" | j: ");
        Serial.println(j);
      }
            
      matrix[matrix_index] = board_matrix[matrix_index];  
    
       
      //matrix[56] = 0;

    }
  }  
  */
  return false; // auto calibrate our board, or don't.
}


// Move the board by a specified amount,
// as specified by x and y
void Board::move(double move_x, double move_y)
{
  

  
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
  if (millis() - start_time < wait) {
    return;  
  }

  
  //Serial.println("MOVE");
  //for (int j=0;j<children.size();j++) {
    
    
  boolean x_collision = false;
  boolean y_collision = false;  
  int j =0;
  /*
  while(j<children.size() && (x_collision==false || y_collision==false) ) {
    x_collision = marble.collides(x+move_x,children[j]->getX());
    y_collision = marble.collides(y+move_y,children[j]->getY());     
    j++; 
  }
  */
  
  

  if (x+move_x < 0-(level_width - 8) ) { move_x = 0; }
  if (x+move_x > 0 ) { move_x = 0; }

  if (y+move_y < 0-(level_height - 8)) { move_y = 0; }
  if (y+move_y > 0) { move_y = 0; }
  
  if (1 || x_collision==false) {
  
  }
  if (1 || y_collision==false) {  
 
    
  }
  boolean debug = false;
  if (debug) {
    
    Serial.print(" x: " );
    Serial.print(move_x);
    Serial.print(" y: " );
    Serial.print(move_y);  
    Serial.println(" ");
    delay(50);
  }
    x += move_x;
    y += move_y;

    
}

