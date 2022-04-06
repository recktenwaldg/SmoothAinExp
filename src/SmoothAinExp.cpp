//  File: SmoothAinExp.cpp
//
//  C++ Code for object-oriented interface for smoothing of analog input readings
//  with an exponentially-weighted average
//
//  Gerald Recktenwald, gerry@pdx.edu
//  2022-02-23

#include "SmoothAinExp.h"

// -- constructor 
SmoothAinExp::SmoothAinExp( int inPin, float alpha ) {

  _inPin = inPin;
  _nReadings = 0;
  _ave = 0.0;
  _aveOld = 0.0;
  _alpha = alpha;
  _oneMinusAlpha = 1.0 - _alpha;  //  Avoid repeated subtraction operation
  _readDelay = 10;                //  delay to allow ADC to settle
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
  uint32_t value;
  
  value = analogRead(_inPin);
  delay(_readDelay);
  value = analogRead(_inPin);
  _lastRaw = value;

  // -- On first reading, set _ave and _aveOld to the first raw value
  //    This sets the initial value of the average to a reasonable value
  //    and is preferable to having the initial value of _aveOld to be zero.
  if ( _nReadings==0 ) {  //  Note:  _nReadings = 0 in constructor
    _ave = (float)value;
    _aveOld = _ave;
    _nReadings = 1;
    return( _ave );
  }
  
  // -- Standard update rule applies to all but the first reading
  _nReadings++;
  _aveOld = _ave;
  _ave= _alpha*(float)value + _oneMinusAlpha*_aveOld;  //  Exp weighted average
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
  _oneMinusAlpha = 1.0 - _alpha;  //  Avoid repeated subtraction operation
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
