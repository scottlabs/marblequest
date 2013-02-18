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
#include "Wall.h"
#include "Marble.h"
#include "Point.h"



class Board
{
  public:
    //Board(double* _matrix, int _cols, int _rows);
    Board();

    boolean draw(double* matrix);

    void move(double move_x, double move_y);

    //double getPointVal(int point_x, int point_y);
    
  private:

    std::vector <Actor *> children;
    //Actor* children[2];
    //std::vector<boost::variant<Marble,Wall> > vec2;
    int start_time;
    int wait;
    int matrix_size;
    int cols;
    int rows;
    int level_width;
    int level_height;    
    double x;
    double y;
};
#endif
