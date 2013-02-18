#define F_CPU 16000000L  // tell code we are 16MHz
#include <util/delay.h>
#include <avr/io.h> 
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>


#include "Point.h"
#include "Marble.h"
#include "Board.h"
#include "LED.h"
#include "Input.h"


LED led;

Board board;
//Board board(level_one1,8,8);
//Board board(level_twoa,11,11);

// the setup routine runs once when you press reset:
void setup() {  


  DDRB=B111111; // 13-8
  DDRC=B001111; // A5-A0
  DDRD=B11111111; // 7-0

  Serial.begin(9600);
  //board.move(0,0);
  
  delay(100);
  
  //Serial.println("Marble Quest!");
  delay(100);
}
Input input;

Point val;


double speed = 0.5;
double cutoff = 0.0;
double matrix[64]; // 8 x 8

int count_debug = 0;

void loop() {


  //Serial.println(1,DEC);return;
  
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
  
  
  
  boolean debug = false;
  if (debug && count_debug > 100000) {
    Serial.print(" move x: ");
  //Serial.print(move_x);
    Serial.print(" move y: ");  
  //Serial.print(move_y);
    Serial.println(" ");
    delay(2000);
    count_debug = 0;
  }
  //count_debug++;
  //move_x = -0.1;
  //move_y = -0.1;
  //board.move(move_x, move_y);
  board.move(move_x, move_y);
  //void move2(double move_x, double move_y);
 
  

  //board.move(1,1);

  boolean auto_calibrate = board.draw(matrix);
  /*
  for (int i=0;i<8;i++) {
    for (int j=0;j<8;j++) {
      //matrix[i+(j*8)] = board.getPointVal(i,j);
      matrix[i+(j*8)] = 1;
      //matrix[i+(j*8)] = 0.2222222;
    } 
  } 
  */

  // arguments
  // matrix - the matrix to draw
  // boolean - whether to calibrate the levels or not. this will automatically adjust power so that a 1 LED looks the same brightness as 8 LEDs.
  led.draw(matrix,auto_calibrate);
  
}


