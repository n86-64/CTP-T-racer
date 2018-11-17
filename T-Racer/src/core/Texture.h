/** @file Texture.h
*  @brief Base class for all textures in the system.
*
*  Define a 2D texture which can then be loaded into an object at any time.
*  Utalises a custom template so either 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <cmath>
#include "helpers/Math_Colour.h"

template<class T>
class T_racer_Texture2D 
{
public:
	T_racer_Texture2D() = default;
	T_racer_Texture2D(int texWidth, int texHeight);
	
	~T_racer_Texture2D() 
	{
		if (textureData) 
		{
			delete[] textureData;
			textureData = nullptr;
		}
	}

	// TODO - Add custom copy constructor for texture.
	void copyPixelValues(int x, int y, T r, T g, T b);

	// perform bi-linear interpolation on the point using a UV poijnt (normalised between 0 and 1)
	T_racer_Math::Colour  interpolatePointBilinear(float u, float v);

private:
	int width = 0;
	int height = 0;
	T*  textureData = nullptr;
	float pixelSize = 0;
};

template<class T>
inline T_racer_Texture2D<T>::T_racer_Texture2D(int texWidth, int texHeight)
	:width(texWidth),
	height(texHeight)
{
	textureData = new T[width * height * (sizeof(T) * 3)];
}

template<class T>
inline T_racer_Math::Colour T_racer_Texture2D<T>::interpolatePointBilinear(float u, float v)
{
	// Values for interpolation.
	T_racer_Math::Vector  q0 = T_racer_Math::Vector(0, 0);
	T_racer_Math::Vector  q1 = T_racer_Math::Vector(width, 0);
	T_racer_Math::Vector  q2 = T_racer_Math::Vector(0, height);
	T_racer_Math::Vector  q3 = T_racer_Math::Vector(width, height);

	// Compute the positions in the x-axis.
	T_racer_Math::Vector posXA = q0 * (1.0f - u) + q1 * u;
	T_racer_Math::Vector posXB = q2 * (1.0f - u) + q3 * u;
	T_racer_Math::Vector interpolatedPos = posXA * (1.0f - v) + posXB * v;

	// Here we obtain the pixel values
	interpolatePos.X = ceil(interpolatePos.X);
	interpolatePos.Y = ceil(interpolatePos.Y);

	// Return the colour in the corrisponding pixel.
	return T_racer_Math::Colour();
}
