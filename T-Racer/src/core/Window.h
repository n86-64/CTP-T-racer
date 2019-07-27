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

class T_racer_Display_Window : public T_racer_Display 
{
public:
	T_racer_Display_Window() = default;
	~T_racer_Display_Window() = default;

	// Inherited via T_racer_Display
	void init(float resolutionX, float resolutionY) override;
	void update() override;
    void writeToDisplay(Image* imageBuffer) override;
	void clear() override;

	void setDisplayName(std::string name) override { displayName = name; window.setTitle("T-Racer Render Result: " + name); } 

	bool shouldQuit() const { return quit; }

private:
	void copyImageToFramebuffer();
	sf::Color  getColour(T_racer_Math::Colour& col);

private:
	sf::Event			  events;
	sf::RenderWindow	  window;

	// Textures for rendering the frame.
	sf::RenderTexture     frameTexture;
	sf::Texture			  winTex;
	sf::Sprite			  winSprite;
};