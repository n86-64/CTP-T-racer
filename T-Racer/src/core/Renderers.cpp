#include "Renderers.h"

void T_racer_Renderer_Base::setDisplay(T_racer_Display * newDisplay)
{
	display = newDisplay;
	threadCount = std::thread::hardware_concurrency();

	if (threadCount > 0) 
	{
		tileThreads.resize(threadCount);
		tileSize = T_racer_Math::Vector(20, 20);
		float tileArea = tileSize.X * tileSize.Y;
		tileCount = floor((display->getWidth() * display->getHeight()) / tileArea);
	}
}
