/*
  Board.h - The class definition for our board.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/
#ifndef Board_h
#define Board_h

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>


#include "Arduino.h"
#include "Marble.h"
#include "Point.h"



class Board
{
  public:
    Board();
    boolean draw(double* matrix);
    void move(double move_x, double move_y);
  private:
    std::vector <Actor *> children;
    unsigned int start_time;
    unsigned int wait;
    int matrix_size;
    int cols;
    int rows;
    int level_width;
    int level_height;    
    double x;
    double y;
    
    unsigned int level_time;
    unsigned int level_wait;
    
    int level_state;
    void level_one();
    void level_one_populate();
    void complete_level();
    
    boolean auto_calibrate;
    boolean populated;
    
    boolean playing;
};
#endif
