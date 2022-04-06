//  File:  demoSmoothAinExp.ino
//
//  Use an exponential-weighted average to smooth readings on an analog input
//  channel.  Also show the last reading so users can compare the raw and
//  smoothed values.
//
//  Gerald Recktenwald, gerry@pdx.edu, v1.0, 2022-02-25

#if defined(ARDUINO_NRF52_ADAFRUIT)
#include <Adafruit_TinyUSB.h>   //  Required by the Adafruit Feather nRF52840 Sense
#endif

// -- Include the SmoothAinExp library and create a SmoothAinExp object
#include <SmoothAinExp.h>
SmoothAinExp vin = SmoothAinExp(A3,0.2);  //  Connect on pin A3, smooth with alpha = 0.2

// ---------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
}

// ---------------------------------------------------------------------
void loop() {
  int   rawReading;   //  Un-smoothed value used for comparison only
  float reading;      //  Smoothed value from analog input

  // -- The .updateAve() method makes a new reading and returns a new averaged value
  reading = vin.updateAve();

  // -- The .lastValue() method retrieves the last raw value that was used to compute
  //    the smoothed (averaged) result.  No new reading is made to obtain the last
  //    raw value.  We are just retrieving the raw value for demonstration purposes.
  rawReading = vin.lastValue();
  
  Serial.print(rawReading);         //  Print raw value for comparison
  Serial.print("\t");
  Serial.println(reading);          //  Print smoothed value
  delay(50);                        //  Slow down the display a little
}
