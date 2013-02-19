#define F_CPU 16000000L  // tell code we are 16MHz
#include <util/delay.h>
#include <avr/io.h> 
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
#include <cstdlib>


#include "Point.h"
#include "Marble.h"
#include "Board.h"
#include "LED.h"
#include "Input.h"
#include "Fade.h"


LED led;
Board board;

//Board board(level_one1,8,8);
//Board board(level_twoa,11,11);

unsigned int start_time;
// the setup routine runs once when you press reset:
void setup() {  


  DDRB=B111111; // 13-8
  DDRC=B001111; // A5-A0
  DDRD=B11111111; // 7-0

  Serial.begin(9600);
  //board.move(0,0);
  
  start_time = millis();

}
Input input;

Point val;


double speed = 0.4;
double cutoff = 0.1;
double matrix[64]; // 8 x 8

int count_debug = 0;
//Fade::Fade(int _x, int _y, int _width, int _height, double _speed, boolean _repeat, double temp, boolean temp_up)
//Fade intro_fade(0,0,8,8,0.03,false,2,false);  
void loop() {

  boolean auto_calibrate = false;
  
  if (0 && millis() - start_time < 2200) {
    for (unsigned int i = 0;i<64;i++) {
      matrix[i] = 0;
    }
    //intro_fade.draw(matrix,8,8);


  } else {
    ///intro_fade = null;
    //Serial.println("draw");    
    //input.calibrate();return;
    val = input.val();
  
    //val.x = -2;
    //val.y = -2;
    
    double move_x = 0;
    double move_y = 0;
    //Serial.println(val.x);
    if (val.x <-1*cutoff) {
      move_x = 1 * speed * val.x;
    } 
    else if (val.x > cutoff) {
      move_x = speed * val.x;
    }
    if (val.y < -1 * cutoff) {
      move_y = 1 * speed * val.y;
    } 
    else if (val.y > cutoff) {
      move_y = speed * val.y;
    }
    board.move(move_x, move_y);
    
    boolean auto_calibrate = board.draw(matrix);
    

  }
  
  // arguments
  // matrix - the matrix to draw
  // boolean - whether to calibrate the levels or not. this will automatically adjust power so that a 1 LED looks the same brightness as 8 LEDs.
    
  led.draw(matrix,auto_calibrate);
}


