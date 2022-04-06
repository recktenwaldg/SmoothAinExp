//  File: SmoothAinExp.h
//
//  Header for object-oriented interface for smoothing of analog input readings
//  with a running average
//
//  Gerald Recktenwald, gerry@pdx.edu
//  2020-12-24


#ifndef SMOOTH_AIN_EXP_h

#define SMOOTH_AIN_EXP_h
#include "Arduino.h"
#include "math.h"


class SmoothAinExp {

	public:
		SmoothAinExp(int inPin, float alpha);

		void insertValue(uint32_t value);
		void printValues(void);
		void setAlpha(float alpha);
		void setReadDelay(int nms);

		float updateAve(void);
		float getAlpha(void);

		uint32_t lastValue(void);

	private:

		int _inPin;
		int _readDelay;   // Make two ADC readings separated by _readDelay milliseconds
		
		float _alpha;
		float _oneMinusAlpha;
        float _ave;
        float _aveOld;
        
		uint32_t _nReadings;
        uint32_t _lastRaw;     
};

#endif


