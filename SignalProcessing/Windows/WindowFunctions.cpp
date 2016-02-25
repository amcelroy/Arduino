/*
 * WindowFunctions.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: mcelr
 */

#include "WindowFunctions.h"

WindowFunctions::WindowFunctions() {
	_Length = 0;
	LUT_32f = NULL;
	LUT_64f = NULL;
}

WindowFunctions::~WindowFunctions() {
	if(LUT_32f != NULL){
		delete[] LUT_32f;
	}

	if(LUT_64f != NULL){
		delete[] LUT_64f;
	}
}

float WindowFunctions::getWindowValueAt_32f(unsigned int Index){
	return LUT_32f[Index];
}

double WindowFunctions::getWindowValueAt_64f(unsigned int Index){
	return LUT_64f[Index];
}

WindowFunctions::WINDOW_FUNC_RETURN WindowFunctions::applyWindow(float Input[], unsigned int InputLength){
	if(LUT_32f == NULL)
		return FLOAT_NOT_INIT;

	if(_Length == InputLength){

		for(unsigned int i = 0; i < _Length; i++){
			Input[i] *= LUT_32f[i];
		}

		return SUCCESS;
	}else{
		return LENGTH_ERROR;
	}
}

WindowFunctions::WINDOW_FUNC_RETURN WindowFunctions::applyWindow(float Input[],
															unsigned int InputLength,
															float Output[],
															unsigned int OutputLength){
	if(LUT_32f == NULL)
		return FLOAT_NOT_INIT;

	if(_Length == InputLength && _Length == OutputLength){

		for(unsigned int i = 0; i < _Length; i++){
			Output[i] = Input[i] * LUT_32f[i];
		}

		return SUCCESS;
	}else{
		return LENGTH_ERROR;
	}
}

WindowFunctions::WINDOW_FUNC_RETURN WindowFunctions::applyWindow(double Input[], unsigned int InputLength){
	if(LUT_64f == NULL)
		return DOUBLE_NOT_INIT;

	if(_Length == InputLength){

		for(unsigned int i = 0; i < _Length; i++){
			Input[i] *= LUT_64f[i];
		}

		return SUCCESS;
	}else{
		return LENGTH_ERROR;
	}
}

WindowFunctions::WINDOW_FUNC_RETURN WindowFunctions::applyWindow(double Input[],
															unsigned int InputLength,
															double Output[],
															unsigned int OutputLength){
	if(LUT_64f == NULL)
		return DOUBLE_NOT_INIT;

	if(_Length == InputLength && _Length == OutputLength){

		for(unsigned int i = 0; i < _Length; i++){
			Output[i] = Input[i] * LUT_64f[i];
		}

		return SUCCESS;
	}else{
		return LENGTH_ERROR;
	}
}


void WindowFunctions::initHanning_32f(unsigned int Length){
	_Length = Length;
	LUT_32f = new float[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_32f[i] = .5*(1 - cosf(2*M_PI*(float)i/((float)Length - 1)));
	}
}

void WindowFunctions::initHanning_64f(unsigned int Length){
	_Length = Length;
	LUT_64f = new double[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_64f[i] = .5*(1 - cos(2*M_PI*(double)i/((double)Length - 1)));
	}
}

void WindowFunctions::initHamming_32f(unsigned int Length, float Alpha, float Beta){
	_Length = Length;
	LUT_32f = new float[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_32f[i] = Alpha - Beta * cosf(2*M_PI*(float)i/((float)Length - 1));
	}
}

void WindowFunctions::initHamming_64f(unsigned int Length, double Alpha, double Beta){
	_Length = Length;
	LUT_64f = new double[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_64f[i] = Alpha - Beta * cos(2*M_PI*(double)i/((double)Length - 1));
	}
}

void WindowFunctions::initTriangle_32f(unsigned int Length){
	_Length = Length;
	LUT_32f = new float[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_32f[i] = 1 - fabsf((i - (Length - 1)/2)/((Length - 1)/2));
	}
}

void WindowFunctions::initTriangle_64f(unsigned int Length){
	_Length = Length;
	LUT_64f = new double[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_64f[i] = 1 - fabs((i - (Length - 1)/2)/((Length - 1)/2));
	}
}

void WindowFunctions::initWelch_32f(unsigned int Length){
	_Length = Length;
	LUT_32f = new float[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_32f[i] = 1 - powf((i - (Length - 1)/2)/((Length - 1)/2), 2);
	}
}

void WindowFunctions::initWelch_64f(unsigned int Length){
	_Length = Length;
	LUT_64f = new double[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_64f[i] = 1 - pow((i - (Length - 1)/2)/((Length - 1)/2), 2);
	}
}

void WindowFunctions::initPowerOfCosine_32f(unsigned int Length, float Power){
	_Length = Length;
	LUT_32f = new float[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_32f[i] = cosf(M_PI*(float)i/((float)Length - 1) - M_PI/2);
	}
}

void WindowFunctions::initPowerOfCosine_64f(unsigned int Length, double Power){
	_Length = Length;
	LUT_64f = new double[Length];

	for(unsigned int i = 0; i < Length; i++){
		LUT_64f[i] = cos(M_PI*(double)i/((double)Length - 1) - M_PI/2);
	}
}
