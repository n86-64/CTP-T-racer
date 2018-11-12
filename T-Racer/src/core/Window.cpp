#include "Window.h"

void T_racer_Display_Window::init(float resolutionX, float resolutionY)
{
	window.create(sf::VideoMode(resolutionX, resolutionY),"T-Racer Result.");
	frameTexture.setView(window.getView());
}

void T_racer_Display_Window::update()
{
	while (window.pollEvent(events)) 
	{
		switch (events.type) 
		{
		case sf::Event::Closed:
			quit = true;
			break;
		}
	}

	window.clear();
	window.display();
}

void T_racer_Display_Window::writeToDisplay(Image& imageBuffer)
{
	frameBuffer = imageBuffer;
}
