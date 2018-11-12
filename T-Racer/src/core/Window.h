/** @file Window.h
*  @brief A basic display that shows images.
*
*  A display which shows the output of the image to the
*  end user.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Display.h"

class T_racer_Display_Window : T_racer_Display 
{
public:
	T_racer_Display_Window() = default;

	// Inherited via T_racer_Display
	void init(float resolutionX, float resolutionY);
	void update();
    void writeToDisplay(Image & imageBuffer);

	bool shouldQuit() const { return quit; }

private:
	sf::Event			  events;
	sf::RenderWindow	  window;
	sf::RenderTexture     frameTexture;
};