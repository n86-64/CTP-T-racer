#include <math.h>
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
	copyImageToFramebuffer();
	window.display();
}

void T_racer_Display_Window::writeToDisplay(Image& imageBuffer)
{
	frameBuffer = imageBuffer;
}

void T_racer_Display_Window::copyImageToFramebuffer()
{
	sf::Image frameImage;
	T_racer_Math::Colour col;
	for (int i = 0; i < frameBuffer.height; i++) 
	{
		for (int j = 0; j < frameBuffer.width; j++)
		{
			col = frameBuffer(i, j);
			frameImage.setPixel(i, j, getColour(col));
		}
	}
}

sf::Color T_racer_Display_Window::getColour(T_racer_Math::Colour & col)
{
	T_racer_Math::Vector3 mappedCol = col.getTonemappedColour(1.0f);
	return sf::Color
	(
		mappedCol.X,
		mappedCol.Y,
		mappedCol.Z
	);
}
