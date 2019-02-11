#include "Renderers.h"

void T_racer_Renderer_Base::setDisplay(T_racer_Display * newDisplay)
{
	display = newDisplay;
	threadCount = std::thread::hardware_concurrency() - 1;
	tileThreads.resize(threadCount);
	tileCount = (int)floor(display->getHeight());
}
