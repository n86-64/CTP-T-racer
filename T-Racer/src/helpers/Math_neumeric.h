/** @file Math_neumeric.h
*  @brief Contains helper neumeric functions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

inline void swap(float& a, float& b) 
{
	float temp = b;
	b = a;
	a = temp;
}

inline float clamp(float val, float low, float high) 
{
	if (val < low) { return low; }
	else if (val > high) { return high; }

	return val;
}