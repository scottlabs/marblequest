/*********************************************

MARBLE QUEST

Created by Kevin Scott, February, 2013
Released into the public domain.

A game where you are the marble and you roll to your goal.

Input device is an accelerometer, which moves the marble around the goal.

Your time is recorded and used to award you a certain number of hearts after completion of the level.

Most of the code is abstracted out into classes for modularity and clarity of purpose. A bulk of 
the code resides in the Board class.

*********************************************/

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

// variables representing our LED, our input device, and the Board our game lives on.
LED led;
Board board;
Input input;


unsigned int start_time; // record of total time of game

void setup() {  
  // turn all pins to output except for two.
  DDRB=B111111; 
  DDRC=B001111;
  DDRD=B11111111;

  Serial.begin(9600);
  start_time = millis();
}

// variables related to the loop. reads in from the Input device,
// and translates that to movement on the board.
Point val; // variable holding our input's position.
double speed = 0.4; // the speed our marble can move.
double input_cutoff = 0.1; // our input must exceed this threshold to be considered 'valid' input.
double matrix[64]; // 8 x 8


// A flag telling the LED whether to 'calibrate' itself or not. we need this because different power
// levels through each row will result in equal values appearing at different intensities. Therefore,
// we track number of on pins and adjust the brighter rows down to match their dimmer cousins.
//
// Unfortunately, doing this limits the granularity we can use for LED values (if we want to avoid flicker)
// and so this flag allows us to switch between the "playing" state (when we want values to be equivalent and
// smooth gradations of pixel value are less important) and the "world" state (when we want smooth fades for 
// various elements).
boolean auto_calibrate = false;

void loop() {
  val = input.val();
  double move_x = 0;
  double move_y = 0;
  if (val.x < -1* input_cutoff || val.x > input_cutoff) {
    move_x = speed * val.x;
  } 
  if (val.y < -1 * input_cutoff || val.y > input_cutoff) {
    move_y = speed * val.y;
  }
  board.move(move_x, move_y);
  
  auto_calibrate = board.draw(matrix);

  // matrix - the matrix to draw onto the LED
  // auto_calibrate - whether to calibrate the levels or not. this will automatically adjust power so that 
  // 1 LED looks the same brightness as 8 LEDs.
  led.draw(matrix,auto_calibrate);
}
