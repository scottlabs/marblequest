#define F_CPU 16000000L  // tell code we are 16MHz
#include <avr/delay.h>
#include <avr/io.h> 
/*------- Hardware configuration -------*/
boolean direction = true;
int current_pin = 0;
const int  pinOne = 7;           // pin One
const int  pinTwo = 6;           // pin Two
const int  pinThree = 5;         // pin Three
const int  pinFour = 4;          // pin Four
const int  pins[4] = {pinOne, pinTwo, pinThree, pinFour};

const int speaker = 8;

const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
                                 // (most Arduino's have a built in LED on pin 13...)

void debugIndicator() {
  
  digitalWrite(debugPin,HIGH); 
  delay(250); 
  digitalWrite(debugPin,LOW);
  delay(80);   
  digitalWrite(debugPin,HIGH); 
  delay(250); 
  digitalWrite(debugPin,LOW);
  delay(80);     
  digitalWrite(debugPin,HIGH); 
  delay(500); 
  digitalWrite(debugPin,LOW);
}
/*-------------------------------------------*/

#include "Tone.h"
#include <math.h>
Tone tone1;

void drumHit() {
  
  for (int i=0;i<20;i++) {

    tone1.play(1175,1);
    _delay_ms(1);    
    tone1.play(400,1);
    _delay_ms(1);    
    tone1.play(1000,1);
    _delay_ms(1);        
  }
}

void setup()
{
  tone1.begin(8);
  
  
  

  /*
  tone1.play(NOTE_A4,100);
  _delay_ms(500);
  tone1.play(NOTE_A5,100);
  _delay_ms(500);
 
  tone1.play(NOTE_A4,100);
  _delay_ms(500);
  tone1.play(NOTE_A5,100);
  _delay_ms(500);

  tone1.play(NOTE_A3,1500);
  _delay_ms(1500);
  tone1.play(NOTE_E3,250);
  _delay_ms(250);
  tone1.play(NOTE_F3,2250);
  _delay_ms(2250);  
  
  */
  
}


void loop()
{
    drumHit();
  _delay_ms(1500);      
}

