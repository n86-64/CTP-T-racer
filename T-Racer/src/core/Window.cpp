#include <math.h>
#include "Window.h"

void T_racer_Display_Window::init(float resolutionX, float resolutionY)
{
	sf::Image iconTex;
	iconTex.loadFromFile("icon.png");
	window.create(sf::VideoMode(resolutionX, resolutionY),"T-Racer Result.");
	window.setIcon(32, 32, iconTex.getPixelsPtr());
	frameTexture.create(resolutionX, resolutionY);
	frameTexture.setView(window.getView());

	resX = resolutionX;
	resY = resolutionY;

	frameBuffer = new Image(resX, resY);
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

	copyImageToFramebuffer();
	window.display();
}

void T_racer_Display_Window::writeToDisplay(Image* imageBuffer)
{
	frameBuffer = imageBuffer;
}

void T_racer_Display_Window::clear()
{
	copyImageToFramebuffer();
	window.display();
}

void T_racer_Display_Window::copyImageToFramebuffer()
{
	sf::Image frameImage = frameTexture.getTexture().copyToImage();
	T_racer_Math::Colour col;
	for (int y = 0; y < frameBuffer->height; y++) 
	{
		for (int x = 0; x < frameBuffer->width; x++)
		{
			col = (*frameBuffer)(x, y) / (*frameBuffer).getAugValue(x, y);
			frameImage.setPixel(x, y, getColour(col));
		}
	}

	winTex.loadFromImage(frameImage);
	winSprite.setTexture(winTex);
	window.draw(winSprite);
}

sf::Color T_racer_Display_Window::getColour(T_racer_Math::Colour& col)
{
	T_racer_Math::Vector mappedCol = col.getTonemappedColour(1.0f / 2.2f);
	return sf::Color
	(
		mappedCol.X,
		mappedCol.Y,
		mappedCol.Z
	);
}
