/** @file TGADisplay.h
*  @brief A basic display that writes output to a TGA file.
*
*  A display which writes the framebuffer output to a TGA file.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "Display.h"

class T_racer_Display_TGA : public T_racer_Display 
{
public:
	T_racer_Display_TGA() = default;

	// Inherited via T_racer_Display
	void init(float resolutionX, float resolutionY) override;
	void update() override { writeToDisplay(this->frameBuffer); };

	// Code for writing to a TGA file is provided by Tom-Bashord Rodgers.
	void writeToDisplay(Image* imageBuffer) override;


	void setDisplayName(std::string name) override;

private:

};