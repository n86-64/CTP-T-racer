#include "Texture.h"

T_racer_Texture2D::T_racer_Texture2D(int texWidth, int texHeight)
	:width(texWidth),
	height(texHeight)
{
	textureData = new float[width * height * 3];
}


void T_racer_Texture2D::copyPixelValues(int x, int y, float r, float g, float b)
{
	int index = x + (y * height);
	textureData[index] = r;
	textureData[index + 1] = g;
	textureData[index + 2] = b;
}


T_racer_Math::Colour T_racer_Texture2D::interpolatePointBilinear(float u, float v)
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
	interpolatedPos.X = ceil(interpolatedPos.X);
	interpolatedPos.Y = ceil(interpolatedPos.Y);

	// Return the colour in the corrisponding pixel.
	return T_racer_Math::Colour();
}