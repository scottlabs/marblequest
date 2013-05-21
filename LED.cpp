/*
  LED.h - The class definition for our LED matrix.
  
  This takes an 8x8 matrix of doubles and translates that to
  the LED 8x8 matrix.
  
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/

#include "Arduino.h"
#include "LED.h"

// our column and row assignments
int cols[8] = {A0, 4, 5, 11, 7, 12, A2, A3};
int rows[8] = {10, A1, 9, 13, 2, 8, 3, 6};

// an array we feed to our Ports
int default_port_vals[3] = {B000000, B000000, B00000000};

// Constructor. Set all our port values to 0.
LED::LED()
{
  for (int i=0;i<8;i++) {
    setPortVals(default_port_vals, cols[i], 0);
    setPortVals(default_port_vals, rows[i], 0);    
  }    
}

// an integer to remember which column we're drawing.
int current_row[8];

// This method takes an 8x8 matrix and a boolean (whether to calibrate levels)
// and translates that into draw instructions for the device.
void LED::draw(double* matrix, boolean calibrate_levels) {

  // internal counters
  int matrix_index;
  double pixel;  
  double total_pixel_count;
  int total_cycle_count;
  int matrix_counter[64];
  
  // total cycle counts is the number of times we will loop through a draw "cycle" 
  // and determines the granularity we can rely on for our values. A higher cycle 
  // count will allow for more granularity of values (and thus is good for fades)
  // but especially if the scene is complicated, too high of a cycle count can result
  // in flickering. So its a trade off.
  // 
  // A solution to that tradeoff is to turn on and off calibration depending on what is
  // needed.
  if (calibrate_levels) {
    total_cycle_count = 4; //we need to lower our threshold to reduce flickering
  } else {
    total_cycle_count = 10; //no fancy pants math so we can have more levels of gradation for fading.
  }
  
  // initialize our matrix to write values to.
  for (int i =0;i<64;i++) {
     matrix_counter[i] = 0;
  }
  
  // loop for a certain cycle count, specified above.
  for (int cycle_count=0;cycle_count<total_cycle_count;cycle_count++) {
    // loop through each column.
    for (int col=0;col<8;col++) {
      total_pixel_count = 0; // counter to remember how many non-0 LED's we have in a column.
      
      // calculate our total LED's per row (but only if we are calibrating levels)
      if (calibrate_levels) {  
        for (int row=0;row<8;row++) {
          matrix_index = row+(8*(col)); // go from the bottom up, based on the wiring of the board.
          pixel = matrix[matrix_index];
  
          if (pixel > 0) {
            total_pixel_count += 1; // count the pixel if non-zero.
          }
        }
      }
      
      // now loop through each row in order to set the Pixel.
      for (int row=0;row<8;row++) {
        matrix_index = row+(8*(col)); // go from the bottom up, based on the wiring of the board.
        pixel = matrix[matrix_index];
        
        if (calibrate_levels) {
          pixel = parsePixel(pixel,total_pixel_count,col);
        }        
        
        current_row[row] = 0;
        
        int division = total_cycle_count;
        int mod_division = round(division * pixel);
        
        
        // this is a bit of a naive approach, but time limitations prevented
        // solution two from being implemented.
        //
        // In approach #1, we compare the current cycle count (which we are incrementing
        // a certain amount of times, as specified above) and if that remains below 
        // mod_division, which is a threshold set according to the pixel value floating number, 
        // then the pixel is on. Otherwise, it is off.
        //
        // This approximates the pixel having a variable brightness, at least at lower numbers
        // of cycles.
        if (1) {
          if (cycle_count % division < mod_division) {
            current_row[row] = 1;
          }  
          
          
          
        // A better approach, detailed below but buggy, uses the same basic idea as above,
        // with the addition that it attempts to evenly space out the 1's and 0's over time.
        // theoretically this would allow us to use 255 cycle counts for a maximum amount of
        // granularity and a minimum of flickering.
        //
        // Unfortunately, bugs exist which I cannot fix.
        } else {
           int matrix_counter_index = row + (col*8);
                     
          if (matrix_counter[matrix_counter_index]==1) {
            current_row[row] = 1;
          }
          matrix_counter[matrix_counter_index] += 1;
        
          float division_of_pixel;
        
          if (pixel > 0) {
            division_of_pixel = 1 / pixel;   
          } else {
            division_of_pixel = 0;
          }

          if (matrix_counter[matrix_counter_index] >= division_of_pixel) {
             matrix_counter[matrix_counter_index] = 0;
          } 
        }
        
      }
      drawRow(cols[col],current_row); // finally, we draw our current row.
    }
  }
}
// call the above with auto calibrate set to true.
void LED::draw(double* matrix) {
  draw(matrix,true); 
}

// Rows' values are inverted when it comes to turning them on and off;
// this method takes care of that.
int LED::invertInt(int i) {
  if (i==1) { i = 0; }
  else if (i==0) { i = 1; }
  return i;
}

// The method that actually takes care of writing the values to the Ports.
void LED::drawRow(int index, int* row_vals) {
  int port_vals[3] = {default_port_vals[0], default_port_vals[1], default_port_vals[2]};
  setPortVals(port_vals, index, 1); // turn on the column.
  for (int i=0;i<8;i++) {
    setPortVals(port_vals, rows[i], invertInt(row_vals[i])); // this will loop through each row and turn it on, or off.
  }
  
  PORTB=port_vals[0];
  PORTC=port_vals[1];
  PORTD=port_vals[2];
}

// This method translates a particular pin or column, along with a particular value,
// into an integer we can then feed to our Ports.
void LED::setPortVals(int* vals, int index, int val) {

  if (index<=7) {
    // port d 
    if (val) {
      vals[2] |= (1<<index); // turn on the index  
    } else{
      vals[2] &= ~(1<<index); // turn off the index
    }
  } else if (index<=13) {
    // port b 
    index -= 8;
    if (val) {
      vals[0] |= (1<<index); // turn on the index  
    } else{
      vals[0] &= ~(1<<index); // turn off the index
    }
  } else {
    // port c
    index -= 14;    
    if (val) {
      vals[1] |= (1<<index); // turn on the index  
    } else{
      vals[1] &= ~(1<<index); // turn off the index
    }
  }
}




// These 2 methods do some very messy re-calibration of values,
// to attempt to get all the LED's displaying at the same brightness.
// Its not perfect but it gets pretty close.
// Total pixel count is how many non-0 LED's are lit up in a row.
double LED::parsePixel(double pixel, int total_pixel_count, int col) { 
  if (pixel >0 ) {
    pixel = parsePixel(pixel, total_pixel_count);
  }
  if (col==7 && total_pixel_count == 1) {
    pixel = pixel / 2;
  }
  return pixel;
}
double LED::parsePixel(double pixel, int total_pixel_count) {  
  if (total_pixel_count==1) {
    if (pixel==1.00) {
      pixel = pixel / 10 * 4;  
    } else {
      pixel = pixel / 10 * 8;  
    }
    
  } else if (total_pixel_count==2) {
    if (pixel==1.00) {
      pixel = pixel / 10 * 5;  
    } else {
      pixel = pixel / 10 * 8;
    }
    
    
  } else if (total_pixel_count==3) {
    pixel = pixel / 10 * 8;
  } else if (total_pixel_count==4) {
    pixel = pixel / 10 * 9;
  } else if (total_pixel_count==5) {
    pixel = pixel * 1.2;
  } else if (total_pixel_count==6) {
    pixel = pixel * 1.5;
  } else if (total_pixel_count==7) {
    pixel = pixel * 2;
  }
  return pixel; 
}
