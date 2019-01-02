#include "Display.h"

void T_racer_Display::setColourValue(int x, int y, T_racer_Math::Colour newCol)
{
	(*frameBuffer)(x, y, newCol);
}
