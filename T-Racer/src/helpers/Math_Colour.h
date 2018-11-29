/** @file Math_Colour.h
*  @brief A colour data structure.
*
*  Defines a container for RGB colour data.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <math.h>

#include "Math_Vector.h"

namespace T_racer_Math 
{
	struct Colour 
	{
		Colour() = default;
		Colour(float r, float g, float b) 
		{
			colour = Vector(r, g, b);
		}

		Vector  colour	   = Vector(1.0f, 1.0f, 1.0f);
		Vector	 luminance = Vector(1.0f, 1.0f, 1.0f);  // Weighting of colour values.

		Vector getLuminanceColour() { return (colour * luminance); };
		Vector getTonemappedColour(float gamma) 
		{
			return Vector
			(
				fmin(1.0f, powf(colour.X, gamma)) * 255,
				fmin(1.0f, powf(colour.Y, gamma)) * 255,
				fmin(1.0f, powf(colour.Z, gamma)) * 255
			);
		}
	};
}