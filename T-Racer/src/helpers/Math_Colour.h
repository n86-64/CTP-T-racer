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
		Vector3  colour	   = Vector3(0.0f, 0.0f,0.0f);
		Vector3	 luminance = Vector3(1.0f, 1.0f, 1.0f);  // Weighting of colour values.

		Vector3 getLuminanceColour() { return (colour * luminance); };
	};
}