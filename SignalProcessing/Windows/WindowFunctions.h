/*
 * WindowFunctions.h
 *
 *  Created on: Feb 20, 2016
 *      Author: mcelr
 */


#ifndef WINDOWS_WINDOWFUNCTIONS_H_
#define WINDOWS_WINDOWFUNCTIONS_H_

#include <stdlib.h>
#include <math.h>
/**
 * This library is free to use and encapsulates signal processing windows that can be used to help suppress
 * artifacts when working with analog data arrays.
 */

class WindowFunctions {
private:
	unsigned int _Length;
	float *LUT_32f;
	double *LUT_64f;

public:
	/**
	 * Quick enumerations to check the output of applyWindow, 1 is good, anything else is not good.
	 * FLOAT_NOT_INIT: Tried to apply a _32f window without initialization
	 * DOUBLE_NOT_INIT: Tried to apply a _64f window without initialization
	 * LENGTH_ERROR: Length of the window didn't match the length of the input or output array
	 */
	enum WINDOW_FUNC_RETURN { SUCCESS = 1, FLOAT_NOT_INIT, DOUBLE_NOT_INIT, LENGTH_ERROR };

	WindowFunctions();
	~WindowFunctions();

	/**
	 * Creates a 32-bit float look-up table for a Hanning Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initHanning_32f(unsigned int Length);

	/**
	 * Creates a 64-bit float look-up table for a Hanning Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initHanning_64f(unsigned int Length);

	/**
	 * Creates a 32-bit float look-up table for a Triangle Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initTriangle_32f(unsigned int Length);

	/**
	 * Creates a 64-bit float look-up table for a Triangle Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initTriangle_64f(unsigned int Length);

	/**
	 * Creates a 32-bit float look-up table for a Welch Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initWelch_32f(unsigned int Length);

	/**
	 * Creates a 64-bit float look-up table for a Welch Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initWelch_64f(unsigned int Length);

	/**
	 * Creates a 32-bit float look-up table for a Hamming Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initHamming_32f(unsigned int Length, float Alpha, float Beta);

	/**
	 * Creates a 64-bit float look-up table for a Hamming Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initHamming_64f(unsigned int Length, double Alpha, double Beta);

	/**
	 * Creates a 32-bit float look-up table for a Parzen Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initPowerOfCosine_32f(unsigned int Length, float Power);

	/**
	 * Creates a 64-bit float look-up table for a Parzen Window. Overwrites any other table.
	 *
	 * @param Length Length of the Window, i.e. 256, 1024, etc
	 */
	void initPowerOfCosine_64f(unsigned int Length, double Power);

	/**
	 * Applies the initialized window to an Input array; overwrites the Input array.
	 * If the Input Length does not equal the initialized Length, the function return LENGTH_ERROR.
	 * If the window is not initialized, function returns FLOAT_NOT_INIT.
	 *
	 * @param Input
	 * @param InputLength
	 * @return SUCCESS, FLOAT_NOT_INIT, LENGTH_ERROR
	 */
	WINDOW_FUNC_RETURN applyWindow(float Input[], unsigned int InputLength);

	/**
	 * Applies the initialized window to an Input array; overwrites the Output array.
	 * If the Input and Output Length does not equal the initialized Length, the function return LENGTH_ERROR.
	 * If the window is not initialized, function returns FLOAT_NOT_INIT.
	 *
	 * @param Input
	 * @param InputLength
	 * @return SUCCESS, FLOAT_NOT_INIT, LENGTH_ERROR
	 */
	WINDOW_FUNC_RETURN applyWindow(float Input[], unsigned int InputLength, float Output[], unsigned int OutputLength);

	/**
	 * Applies the initialized window to an Input array; overwrites the Input array.
	 * If the Input Length does not equal the initialized Length, the function return LENGTH_ERROR.
	 * If the window is not initialized, function returns DOUBLE_NOT_INIT.
	 *
	 * @param Input
	 * @param InputLength
	 * @return SUCCESS, DOUBLE_NOT_INIT, LENGTH_ERROR
	 */
	WINDOW_FUNC_RETURN applyWindow(double Input[], unsigned int InputLength);

	/**
	 * Applies the initialized window to an Input array; overwrites the Output array.
	 * If the Input and Output Length does not equal the initialized Length, the function return LENGTH_ERROR.
	 * If the window is not initialized, function returns DOUBLE_NOT_INIT.
	 *
	 * @param Input
	 * @param InputLength
	 * @return SUCCESS, DOUBLE_NOT_INIT, LENGTH_ERROR
	 */
	WINDOW_FUNC_RETURN applyWindow(double Input[], unsigned int InputLength, double Output[], unsigned int OutputLength);

	/**
	 * Get the Windows value at the Index. Useful if you are writing your own loops
	 * and the applyWindow() functions would be more inefficient. No error checking is done!
	 *
	 * @param Index Index of the value, should be 0 to Length - 1
	 * @return The value of the window at the Index position
	 */
	float getWindowValueAt_32f(unsigned int Index);

	/**
	 * Get the Windows value at the Index. Useful if you are writing your own loops
	 * and the applyWindow() functions would be more inefficient. No error checking is done!
	 *
	 * @param Index Index of the value, should be 0 to Length - 1
	 * @return The value of the window at the Index position.
	 */
	double getWindowValueAt_64f(unsigned int Index);
};

#endif /* WINDOWS_WINDOWFUNCTIONS_H_ */
