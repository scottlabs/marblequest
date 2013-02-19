/*
  LED.h - The class definition for our LED matrix.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "LED.h"

int cols[8] = {A0, 4, 5, 11, 7, 12, A2, A3};
int rows[8] = {10, A1, 9, 13, 2, 8, 3, 6};
int default_port_vals[3] = {B000000, B000000, B00000000};
LED::LED()
{

    //cycleCount = 0; 
    //current_col=0;
    for (int i=0;i<8;i++) {
      setPortVals(default_port_vals, cols[i], 0);
      setPortVals(default_port_vals, rows[i], 0);    
    }   
  
}

void LED::discoverPorts() {
  PORTB=B011000; //13-8
  PORTC=B001101; //A5-A0
  PORTD=B10110000; //7-0 

  Serial.print("Bright Port Vals: ");
  Serial.print(PORTB); // 24  -- 00 00 00 16 8 0 0 0
  Serial.print(" | ");  
  Serial.print(PORTC); // 13  -- 00 00 00 00 8 4 0 1
  Serial.print(" | ");    
  Serial.println(PORTD); //176-- 128 00 32 16 0 0 0 0
}

double LED::parsePixel(double pixel, int total_pixel_count) {  
  if (total_pixel_count==1) {
    pixel = pixel/12*4; 
  } else if (total_pixel_count==2) {
    pixel = pixel/3;
  } else if (total_pixel_count==3) {
    pixel = pixel/3;    
  } else if (total_pixel_count==4) {
    pixel = pixel/3;    
  } else if (total_pixel_count==5) {
    pixel = pixel/3*2;        
  } else if (total_pixel_count==6) {
    pixel = pixel;
  } else if (total_pixel_count==7) {
    pixel = pixel;
  } else {
    pixel = pixel * 3 / 2;
  }
  return pixel; 
}

int current_row[8];
void LED::draw(double* matrix) {
  draw(matrix,true); 
}
void LED::draw(double* matrix, boolean calibrate_levels) {
  

  //delay(50);
  
  // 50 is basically the upper limit
  int matrix_index;
  double pixel;  
  double total_pixel_count;
  int total_cycle_count;
  if (calibrate_levels) {
    total_cycle_count = 4; //we need to lower our threshold to reduce flickering, since we're making math happen
  } else {
    total_cycle_count = 10; //no fancy pants math so we can have more levels of gradation for fading.
  }
  int matrix_counter[64];
  
  for (int i =0;i<64;i++) {
     matrix_counter[i] = 0;
  }
  
  for (int cycle_count=0;cycle_count<total_cycle_count;cycle_count++) {
    for (int col=0;col<8;col++) {
      total_pixel_count = 0;
      
      for (int row=0;row<8;row++) {
        matrix_index = row+(8*(col)); // go from the bottom up        
        pixel = matrix[matrix_index];

        if (pixel > 0) {
          total_pixel_count += 1; 
        }
        //total_pixel_count = total_pixel_count + pixel;
        
        /*
        if (pixel==1 || pixel == 0.5) {
          total_pixel_count++; 
        }*/
      }

        
      for (int row=0;row<8;row++) {
        matrix_index = row+(8*(col)); // go from the bottom up        
        pixel = matrix[matrix_index];
        
        if (calibrate_levels) {
          pixel = parsePixel(pixel,total_pixel_count);
        }        
        
        current_row[row] = 0;
        
        // cycle_count%1<1 | 1
        // cycle_count%2<1 | .5
        // cycle_count%4<1 | .25
        // cycle_count%4<3 | .75
        // cycle_Count%256<128 | .5
        // cycle_count%256<64 | .25
        // cycle_count%256<192 | .75
        
        int division = total_cycle_count;
        int mod_division = round(division * pixel);
        
        
        
        // how do you automatically drill numbers down to their most basic parts?
        // or maybe there's a better way.
        // parse({cycle_count : 0, division : 256, pixel : 0.27});
        // results in:
        // 0 % 256 < 69
        // every 69 cycles out of 256 it's on, then it's off.
        // i want to space those 69 cycles evenly.
        
        /*
        while (mod_division % 2 == 0 && division % 2 == 0) {
          division /= 2;
          mod_division /= 2; 
        }
        */
        // 2 out of 9 times, would be
        // 0 1 0 0 0 0 1 0 0
        // or:
        // 9/2: 4.5
        // start a counter at 0. when it's 1, light it up.
        // every cycle, increment it. when it's greater than total_cycle_count / pixel, reset to 0.
        
        
        
        int approach = 1;
        
        if (approach==1) {
          if (cycle_count % division < mod_division) {
            current_row[row] = 1;
          }  
          
          
          
          
          // what we're trying to do here is evenly space out
          // the ons and offs, so we can divide them better
        } else if (approach == 2) {
           int matrix_counter_index = row + (col*8);
        
        

                     
          if (matrix_counter[matrix_counter_index]==1) {
            current_row[row] = 1;
          }
          matrix_counter[matrix_counter_index] += 1;
        
          float division_of_pixel;
        
          if (pixel > 0) {
            division_of_pixel = 1 / pixel;   
   
   
            
            if (col==0&&row==0&&0) {
            Serial.print("cyclecount: ");
            Serial.println(cycle_count);          
            Serial.print("division: ");
            Serial.println(division);          
            Serial.print("pixel: ");
            Serial.println(pixel);          
            Serial.print("div of pix: ");
            Serial.println(division_of_pixel);       
            }
              
            //division_of_pixel = 1 / (division / pixel);  
          } else {
            division_of_pixel = 0;
          }

          if (matrix_counter[matrix_counter_index] >= division_of_pixel) {
          //if (matrix_counter[matrix_counter_index] >= 8) {
             matrix_counter[matrix_counter_index] = 0;
          } 
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        //delay(5);
        
        /*
        ///// this code successfully handles different output levels 
        if (0) {
          
        } else if (total_pixel_count<=1) {
          if (pixel==1||pixel==0) {
            if (cycle_count%8==0) {
              current_row[i] = pixel;  
            }
          } else {
             // half pixel
            if (cycle_count%16==0) {
              current_row[i] = 1;
            } 
          }
        } else if (total_pixel_count<=2) {
          //current_row[i] = 1;
          if (pixel==0 || pixel==1) {
            if (cycle_count%2==0) {
              current_row[i] = pixel; 
            }
          } else {

            // half pixel
            if (cycle_count%8==0) {
               current_row[i] = 1; 
            }
          }
        } else {
          if (pixel == 1 || pixel == 0) {
            current_row[i] = pixel;    
          } else if (cycle_count%4==0) {
            current_row[i] = 1;
          }
          
        }*/
        
        
        /*
        if (pixel==1 || pixel == 0) {
          current_row[i] = pixel;
          
        } else if (pixel==0.5 && (cycle_count==0 || cycle_count == 2)) {
          current_row[i] = 1;          
        } else if (pixel==0.25 && (cycle_count==0)) {
          current_row[i] = 1;          
        } else {
          current_row[i] = 0;
        }*/
        
      }
      drawRow(cols[col],current_row);
    }
  }
}



int LED::invertInt(int i) {
  if (i==1) { i = 0; }
  else if (i==0) { i = 1; }
  return i;
  //return (i-1)*-1;
}
void LED::drawRow(int index, int* row_vals) {

  

  int port_vals[3] = {default_port_vals[0], default_port_vals[1], default_port_vals[2]};
  setPortVals(port_vals, index, 1);

  
  for (int i=0;i<8;i++) {
    setPortVals(port_vals, rows[i], invertInt(row_vals[i]));

    //setPortVals(port_vals, rows[i], row_vals[i]);  
    
//    delay(1000);
  }

  
  PORTB=port_vals[0]; // 59, // 1 1 1 0 1 1. pins 11 and 12 are turned on.
  PORTC=port_vals[1]; // 15 
  PORTD=port_vals[2]; // 253
  //PORTB=B100011; // 35
  //PORTC=B000011; // 3
  //PORTD=B01001100; // 76

  /*
  Serial.print("Port Vals: ");
  Serial.print(PORTB);
  Serial.print(" | ");  
  Serial.print(PORTC);
  Serial.print(" | ");    
  Serial.println(PORTD);
  */

}



void LED::setPortVals(int* vals, int index, int val) {
  //Serial.println("index and val");
  //Serial.println(index);
  //Serial.println(val);
  if (index<=7) {
    // port d 
    if (val) {
    
      vals[2] |= (1<<index); // turn on the index  
    } else{

      vals[2] &= ~(1<<index); // turn off the index
    }
  } else if (index<=13) {
    //Serial.println("13");
    // port b 
    index -= 8;
    if (val) {
      vals[0] |= (1<<index); // turn on the index  
    } else{
      vals[0] &= ~(1<<index); // turn off the index
    }
  } else {
    index -= 14;    
    // port c
    if (val) {
      vals[1] |= (1<<index); // turn on the index  
    } else{
      vals[1] &= ~(1<<index); // turn off the index
    }
  }
  
  //return vals;
}

