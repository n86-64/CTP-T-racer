/** @file PreviewWindow.h
*  @brief A window to preview the render.
*
*  A window that shows the render result from the framebuffer.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

// Insert SFML headers here.
#include <SFML/Graphics.hpp>

class T_racer_FrameBuffer;

class T_racer_PreviewWindow 
{
public:
	T_racer_PreviewWindow(int width, int height);
	~T_racer_PreviewWindow();

	// Window properties.
	void setWindowTitle(std::string title);
	void setWindowSize(int width, int height);
	void setFramebuffer(T_racer_FrameBuffer* newFB);
	
	// calls.
	void RunWindow();

private:
	void drawFramebuffer();

private:
	// Window properties.
	T_racer_FrameBuffer*  framebufferHND = nullptr;
	bool close = false;
	
	// SFML code for display.
	sf::Event			  events;
	sf::RenderWindow	  window;
	sf::Image			  renderImage;
	sf::Texture			  renderTexture;
};