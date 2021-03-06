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
	Image(int w, int h, T_racer_Math::Colour col) : Image(w, h)
	{
		for (int i = 0; i < getSize(); i++) 
		{
			colour_values[i] = col;
		}
	}

	int getSize() { return width * height; }
	void setSize(int nWidth, int nHeight) 
	{
		width = nWidth;
		height = nHeight;
		colour_values = new T_racer_Math::Colour[width * height] { T_racer_Math::Colour(0.0f, 0.0f, 0.0f) };

	}

	// Copy Constructor for copying values across.
	Image(const Image& image) 
	{
		this->colour_values = new T_racer_Math::Colour[image.width * image.height];
		this->width = image.width;
		this->height = image.height;
		memcpy(&this->colour_values[0], image.colour_values, sizeof(T_racer_Math::Colour) * image.width * image.height);
	}

	Image(int w, int h) 
	{
		width = w;
		height = h;
		colour_values = new T_racer_Math::Colour[w * h];
	};


	T_racer_Math::Colour  operator()(int x, int y) 
	{
		int point = (y * width) + x;
		return colour_values[point];
	}

	void  operator()(int x, int y, T_racer_Math::Colour col)
	{
		int point = (y * width) + x;
		colour_values[point] = col;
	}

	void  operator()(int index, T_racer_Math::Colour col)
	{
		colour_values[index] = col;
	}

	Image operator=(const Image& image) 
	{
		return Image(image);
	}

	~Image() 
	{
		if (colour_values) 
		{
			delete[] colour_values;
			colour_values = nullptr;
		}
	}
};

