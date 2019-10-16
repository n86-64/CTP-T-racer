#include "FrameBuffer.h"
#include "Texture.h"

#include "PreviewWindow.h"

T_racer_PreviewWindow::T_racer_PreviewWindow(int width, int height)
{
	sf::Image iconTex;
	iconTex.loadFromFile("icon.png");
	window.create(sf::VideoMode(width, height), "T-Racer");
	window.setIcon(32, 32, iconTex.getPixelsPtr());
}

T_racer_PreviewWindow::~T_racer_PreviewWindow()
{
	window.close();
}

void T_racer_PreviewWindow::setWindowTitle(std::string title)
{
	window.setTitle(title);
}

void T_racer_PreviewWindow::setWindowSize(int width, int height)
{
	window.setSize(sf::Vector2u(width, height));
}

void T_racer_PreviewWindow::setFramebuffer(T_racer_FrameBuffer* newFB)
{
	framebufferHND = newFB;
}

void T_racer_PreviewWindow::RunWindow()
{
	while (window.pollEvent(events))
	{
		switch (events.type)
		{
		case sf::Event::Closed:
			close = true;
			break;
		}
	}

	drawFramebuffer();
	window.display();
}

void T_racer_PreviewWindow::drawFramebuffer()
{
	if (framebufferHND) 
	{
		T_racer_Texture2D  texture = framebufferHND->fetchFramebufferRaw();
		renderImage.create(framebufferHND->getWidth(), framebufferHND->getHeight());
		T_racer_Math::Colour col;
		for (int y = 0; y < framebufferHND->getHeight(); y++)
		{
			for (int x = 0; x < framebufferHND->getWidth(); x++)
			{
				col.colour = texture.getPixelValue(x,y).getTonemappedColour(1 / 2.2f);
				sf::Color newCol(col.colour.X, col.colour.Y, col.colour.Z);
				renderImage.setPixel(x, y, newCol);
			}
		}
		renderTexture.loadFromImage(renderImage);
		window.draw(sf::Sprite(renderTexture));
	}
}
