#define F_CPU 16000000L  // tell code we are 16MHz
#include <util/delay.h>
#include <avr/io.h> 
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>

#include "notes.c"

int speaker_1 = 9;

int notes[] = {
  NOTE_A3, NOTE_B3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3,
  NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_A5, NOTE_B5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5
};

void death() {
  int length = 10;
  //randomSeed(analogRead(0));


  for (int i = 0; i < 10*10; i++) {
    tone(speaker_1, NOTE_C3, length);
    delay(length);
    tone(speaker_1, NOTE_G3, length);
    delay(length);    
    
  }
}

void setup() {
  int length = 100;// 100 sounds ok
  //length = 10;
  //randomSeed(analogRead(0));
  for (int i = 0; i < 8; i++) {
    tone(speaker_1, NOTE_C3, length);
    delay(length);
    tone(speaker_1, NOTE_G3, length);
    delay(length);    
    
  }
  for (int i = 0; i < 8; i++) {
    tone(speaker_1, NOTE_AS3, length);
    delay(length);
    tone(speaker_1, NOTE_F3, length);
    delay(length);    
    
  }  
  return;
  makeTone(NOTE_D3, 8);
  makeTone(NOTE_C3, 8);  
  makeTone(NOTE_AS2, 24);
  makeTone(NOTE_C3, 8);    
  makeTone(NOTE_D3, 16);    
}

int makeTone(int note, int noteLength) {
  //noteLength *= 4;
  //int noteDuration = 1000/noteLength;
  int noteDuration = 100*noteLength;
  
  int pauseBetweenNotes = noteDuration * 1.0;
  tone(speaker_1, note, noteDuration);
  delay(pauseBetweenNotes);
}

void loop() {
  //makeTone(NOTE_E5, 4*6);
  //makeTone(NOTE_A3, 4*4);
  
  // no need to repeat the melody.
}
