/** @file Image.h
*  @brief An image definition with colour values.
*
*  Defines a collection of colour values. Can be used for information other than
*  Images.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once
#include "helpers/Math_Colour.h"

struct Image 
{
	int							    width = 0;
	int								height = 0;
	T_racer_Math::Colour*			colour_values = nullptr;

	Image() {}; // Constructs a blank image.

	Image(int w, int h) 
	{
		width = w;
		height = h;
		colour_values = new T_racer_Math::Colour[w * h];
	};

	~Image() 
	{
		if (colour_values) 
		{
			delete[] colour_values;
			colour_values = nullptr;
		}
	}
};

