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

#pragma warning (disable : 4996)


#include <string>
#include "helpers/Image.h"

class T_racer_Display 
{
public:
	virtual ~T_racer_Display() = default;

	virtual void init(float resolutionX, float resolutionY) = 0; 
	virtual void update() = 0;
	virtual void writeToDisplay(Image* imageBuffer) = 0;

	virtual void setDisplayName(std::string name) = 0;

	float getWidth() const { return resX; }
	float getHeight() const { return resY; }

protected:
	std::string displayName;
	bool     quit = false;
	Image*    frameBuffer;

	// DEPRECATED!!! - Information is provided by image. 
	float    resX, resY;
};