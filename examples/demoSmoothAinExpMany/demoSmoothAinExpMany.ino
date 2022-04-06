//  File:  demoSmoothAinExpMany.ino
//
//  Use an exponential-weighted average to smooth readings on several analog
//  input channels.  Also show the last reading on each of those channels
//  so users can compare the raw and smoothed values.
//
//  Gerald Recktenwald, gerry@pdx.edu, v1.0, 2022-02-25

#if defined(ARDUINO_NRF52_ADAFRUIT)
#include <Adafruit_TinyUSB.h>   //  Required by the Adafruit Feather nRF52840 Sense
#endif

// -- Include the SmoothAinExp library and create several SmoothAinExp objects
//    Here we connect to the same input channel using different smoothing paramters (alpha)
//    with the goal of comparing the effect of the changing the smoothing.  Normally,
//    if multiple SmoothAinExp objects are used in the same sketch, each of those objects
//    would be connected to a different analog channel
#include <SmoothAinExp.h>
SmoothAinExp vin01 = SmoothAinExp(A3,0.1);  //  Measure pin A3, smooth with alpha = 0.1
SmoothAinExp vin02 = SmoothAinExp(A3,0.2);  //  Measure pin A3, smooth with alpha = 0.2
SmoothAinExp vin05 = SmoothAinExp(A3,0.5);  //  Measure pin A3, smooth with alpha = 0.5

// ---------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
}

// ---------------------------------------------------------------------
void loop() {
  int   raw01;
  float vs01,vs02,vs05;

  // -- Retrieve the smoothed value when different alpha (smoothing parameters) are
  //    applied to the same analog input channel.  For comparison, the raw value for
  //    one SmoothAinExp oject is also printed to the Serial object
  //    This is not an exact comparison, since each SmoothAinExp object will likely
  //    have a different .lastValue().  Note that the .lastValue() method returns
  //    the value of the last raw reading without making another reading
  vs01  = vin01.updateAve();  //  Get the averaged value
  raw01 = vin01.lastValue();  //  Get raw (un-smoothed) value
  vs02  = vin02.updateAve();  //  ... and repeat
  vs05  = vin05.updateAve();

  Serial.print(raw01);
  Serial.print("\t"); Serial.print(vs01);
  Serial.print("\t"); Serial.print(vs02);
  Serial.print("\t"); Serial.println(vs05);

  delay(50);                   //  Slow down the display a little
}
