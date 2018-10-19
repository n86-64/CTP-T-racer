/** @file Math_Colour.h
*  @brief A colour data structure.
*
*  Defines a container for RGB colour data.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "Math_Vector.h"

namespace T_racer_Math 
{
	struct Colour 
	{
		Vector3    colour;
		Vector3	 luminance;  // Weighting of colour values.

		Vector3 getLuminanceColour() { return (colour * luminance); };
	};
}