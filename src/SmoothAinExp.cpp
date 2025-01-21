//  File: SmoothAinExp.cpp
//
//  C++ Code for object-oriented interface for smoothing of analog input readings
//  with an exponentially-weighted average
//
//  Gerald Recktenwald, gerry@pdx.edu, 2022-02-21
//
//  Updates:
//    2022-08-08:
//      * Initialize 

#include "SmoothAinExp.h"

// -- constructor 
SmoothAinExp::SmoothAinExp( int sensorPin, float alpha ) {

  _inPin = sensorPin;
  _nReadings = -1;
  _ave = analogRead(_inPin);   //  Initialize with realistic value, not zero
  _aveOld = _ave;
  _alpha = alpha;
  _readDelay = 10;     //  delay between readings to allow ADC to settle
}

// ------------------------------------------------------------------------------
//   Insert a value into sequence used to compute the exponentially-weighted average
void SmoothAinExp::insertValue(uint32_t value) {
  _nReadings++;
  _aveOld = _ave;
  _ave = value;
}

// ------------------------------------------------------------------------------
//  Get a new reading, update the average
float SmoothAinExp::updateAve(void) {
  
  uint32_t value = analogRead(_inPin);
  delay(_readDelay);
  value = analogRead(_inPin);
  _lastRaw = value;

  if ( _nReadings<0 ) {   //  Insurance that sequence is initialized with realistic value
    _ave = (float)value;  //  Initial value should not be zero
    _aveOld = _ave;       //  and there is no history
    _nReadings = 1;
    return( _ave );
  }
  _nReadings++;
  _ave= _alpha*(float)value + (1.0-_alpha)*_aveOld;  //  Exp weighted average
  _aveOld = _ave;
  return( _ave );
}

// ------------------------------------------------------------------------------
//   Return the exponential-weighting parameter, alpha:  aNew = alpha*reading + (1-alpha)*aOld
float SmoothAinExp::getAlpha(void) {
  return(_alpha);
}

// ------------------------------------------------------------------------------
//   Change the number of values currently used in the running average
void SmoothAinExp::setAlpha(float alpha) {
  _alpha = alpha;
}

// ------------------------------------------------------------------------------
//   Change the delay between readings that is used to allow the ADC to settle
void SmoothAinExp::setReadDelay(int nms) {
  _readDelay = nms;
}

// ------------------------------------------------------------------------------
//   Return the last raw reading used to compute the exponentially weighted average
uint32_t SmoothAinExp::lastValue(void) {
  return(_lastRaw);
}

// ------------------------------------------------------------------------------
//   Print all of the values stored in the buffer
void SmoothAinExp::printValues(void) {

  Serial.print("ave, aveOld = ");
  Serial.print(_ave);
  Serial.print("\t");
  Serial.println(_aveOld);
}
