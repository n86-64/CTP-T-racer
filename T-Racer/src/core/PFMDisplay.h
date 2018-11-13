/** @file PFMDisplay.h
*  @brief A display which renders the file as a PFM.
*
*  Writes the contents of the framebuffer to a PFM object.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "core/Display.h"

class T_racer_Display_PFM : public T_racer_Display
{
public:
	T_racer_Display_PFM() = default;

	// Inherited via T_racer_Display
	void init(float resolutionX, float resolutionY) override;
	void update() override;

	// Code for parsong to a pfm file is provided by 
	// Tom bashford rodgers. 
	void writeToDisplay(Image* imageBuffer) override;


	void setDisplayName(std::string name) override { displayName = name; }

};