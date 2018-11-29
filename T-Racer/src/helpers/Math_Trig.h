/** @file Math_Trig.h
*  @brief A collection of trig operations.
*
*  Defines a collection of trig operations.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#define M_PI       3.14159265358979323846   // pi

inline float radians(float degrees) 
{
	return degrees * (M_PI / 180.0f);
}