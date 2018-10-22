// File - Images.h
// Description - Defines an image. 

#pragma once
#include "helpers/Math_Colour.h"

struct Image 
{
	int							     width = 0;
	int								height = 0;
	T_racer_Math::Colour*			colour_values = nullptr;

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

