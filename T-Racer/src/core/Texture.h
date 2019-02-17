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

struct aiTexture;

class T_racer_Texture2D 
{
public:
	T_racer_Texture2D() = default;
	T_racer_Texture2D(int texWidth, int texHeight);
	T_racer_Texture2D(const T_racer_Texture2D& obj);
	T_racer_Texture2D(aiTexture* newTexture);
	
	~T_racer_Texture2D() 
	{
		if (textureData) 
		{
			delete[] textureData;
			textureData = nullptr;
		}
	}

	// TODO - Add custom copy constructor for texture.
	void copyPixelValues(int x, int y, float r, float g, float b);

	// perform bi-linear interpolation on the point using a UV poijnt (normalised between 0 and 1)
	T_racer_Math::Colour  interpolatePointBilinear(float u, float v);
	T_racer_Math::Colour  getPixelValue(int x, int y);



private:
	int width = 0;
	int height = 0;
	float*  textureData = nullptr;
	float pixelSize = 0;
};
