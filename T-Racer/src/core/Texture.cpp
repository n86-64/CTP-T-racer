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
	float Tu = (u * width);
	float Tv = (v * height);

	int Iu = ((int)floor(Tu)) % width;
	int Iv = ((int)floor(Tv)) % height;

	float wU = Tu - Iu;
	float wV = Tv - Iv;

	// Values for interpolation.
    // Here we will put the nearest pixel values.
	T_racer_Math::Colour   c00 = getPixelValue(Iu, Iv);
	T_racer_Math::Colour   c01 = getPixelValue(Iu + 1, Iv);
	T_racer_Math::Colour   c10 = getPixelValue(Iu, Iv + 1);
	T_racer_Math::Colour   c11 = getPixelValue(Iu + 1, Iv + 1);

	T_racer_Math::Vector colourVec = (c00.colour * (1 - wU) * (1 - wV)) + (c01.colour * wU * (1 - wV)) 
		+ ( c01.colour * (1 - wU) * wV) + (c11.colour * wU * wV);

	T_racer_Math::Colour outCol;
	outCol.colour = T_racer_Math::Vector(colourVec.X, colourVec.Y, colourVec.Z);

	// Return the colour in the corrisponding pixel.
	return outCol;
}

T_racer_Math::Colour T_racer_Texture2D::getPixelValue(int x, int y)
{
	return T_racer_Math::Colour
	(
		textureData[x + (width * y)], 
		textureData[x + (width * y) + 1], 
		textureData[x + (width * y) + 2]
	);
}
