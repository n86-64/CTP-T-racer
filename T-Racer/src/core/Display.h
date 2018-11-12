/** @file Display.h
*  @brief A base display object.
*
*  Defines a skeleton display/rendertarget which is capable of
*  rendering images on screen.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once
#include "helpers/Image.h"
#include "helpers/Math_Colour.h"

class T_racer_Display 
{
public:
	T_racer_Display() = default;
	virtual ~T_racer_Display() = default;

	virtual void init(float resolutionX, float resolutionY) = 0; 
	virtual void update() = 0;
	virtual void writeToDisplay(Image& imageBuffer) = 0;

protected:
	bool     quit = false;
	Image    frameBuffer;
	float    resX, resY;
};