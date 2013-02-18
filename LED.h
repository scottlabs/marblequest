/*
  LED.h - The class definition for our LED matrix.
  Created by Kevin Scott, February 10, 2013
  Released into the public domain.
*/
#ifndef LED_h
#define LED_h

#include "Arduino.h"


class LED
{
  public:
    LED();
    void draw(double* matrix);
    void draw(double* matrix, boolean calibrate_levels);
    void discoverPorts();    
  private:
    void setPortVals(int* vals, int index, int val);
    double parsePixel(double pixel, int total_pixel_count);
    
    int invertInt(int i);
    void drawRow(int index, int* row_vals);
    
    //int cycleCount;
    //int col;

    
};
#endif
