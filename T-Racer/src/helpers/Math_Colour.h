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
		Colour(float rgb) { colour = Vector(rgb, rgb, rgb); }

		Vector  colour	   = Vector(0.0f, 0.0f, 0.0f);
		Vector	 luminance = Vector(1.0f, 1.0f, 1.0f);  // Weighting of colour values.

		float getLuminance() { return dot(colour, Vector(0.2126, 0.7152, 0.0722)); };
		Vector getTonemappedColour(float gamma) 
		{
			return Vector
			(
				fmin(1.0f, powf(colour.X, gamma)) * 255,
				fmin(1.0f, powf(colour.Y, gamma)) * 255,
				fmin(1.0f, powf(colour.Z, gamma)) * 255
			);
		}

		Colour operator*(Colour col) 
		{
			Vector val = this->colour * col.colour;
			return Colour(val.X, val.Y, val.Z);
		}

		//Colour operator*(Colour col)
		//{
		//	Vector val = this->colour * col.colour;
		//	return Colour(val.X, val.Y, val.Z);
		//}

		Colour operator*(float scalier)
		{
			Vector val = this->colour * scalier;
			return Colour(val.X, val.Y, val.Z);
		}

		Colour operator/(float scalier) 
		{
			Vector val = this->colour / scalier;
			return Colour(val.X, val.Y, val.Z);
		}

		// Sets colour to zero if colour value is infinate. Prevents infinite colour values.
		void nanCheck() 
		{
			isnan(colour.X) ? colour.X = 0 : colour.X;
			isnan(colour.Y) ? colour.Y = 0 : colour.Y;
			isnan(colour.Z) ? colour.Z = 0 : colour.Z;
		}
	};
}