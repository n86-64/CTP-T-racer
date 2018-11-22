/** @file Math_neumeric.h
*  @brief Contains helper neumeric functions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

inline float swap(float& a, float& b) 
{
	float temp = b;
	b = a;
	a = temp;
}