#include "Display.h"

void T_racer_Display::setColourValue(int x, int y, T_racer_Math::Colour newCol)
{
	(*frameBuffer)(x, y, newCol);
}

void T_racer_Display::setColourValue(int index, T_racer_Math::Colour newCol)
{
	(*frameBuffer)(index, newCol);
}

void T_racer_Display::incrementColourValue(int x, int y, T_racer_Math::Colour newCol)
{
	(*frameBuffer)(x, y, (*frameBuffer)(x, y) + newCol);
}

void T_racer_Display::incrementColourValue(int index, T_racer_Math::Colour newCol)
{
	(*frameBuffer)(index, (*frameBuffer)(index) + newCol);
}

void T_racer_Display::setSampleCount(int x, int y, int newCount)
{
	(*frameBuffer).setAugValue(x, y, newCount);
}

void T_racer_Display::setSampleCount(int index, int newCount)
{
	(*frameBuffer).setAugValue(index, newCount);
}

void T_racer_Display::setSampleCount(int newCount)
{
	(*frameBuffer).setAugValue(newCount);
}
