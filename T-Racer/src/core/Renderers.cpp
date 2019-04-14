#include <jsoncons/json.hpp>

#include "Window.h"
#include "PFMDisplay.h"
#include "TGADisplay.h"

#include "Renderers.h"

T_racer_Renderer_Base::~T_racer_Renderer_Base()
{
	if (initFromFile && display) 
	{
		delete display;
		display = nullptr;
	}
}

void T_racer_Renderer_Base::setDisplay(T_racer_Display* newDisplay)
{
	display = newDisplay;
	threadCount = std::thread::hardware_concurrency() - 1;
	tileThreads.resize(threadCount);
	tileCount = (int)floor(display->getHeight());
}

void T_racer_Renderer_Base::setDisplay(JSONFileReader displayName)
{
	T_racer_Display* newDisplay = nullptr;
	float x, y;
	std::string name;
	for (auto& properties : displayName.buffer["Display"].members()) 
	{

		if (properties.name() == "Name") { name = properties.value().as_string(); }
		else if (properties.name() == "Type") 
		{
			if (properties.value().as_string() == "Window") { newDisplay = new T_racer_Display_Window(); }
			else if(properties.value().as_string() == "PFM") { newDisplay = new T_racer_Display_PFM(); }
			else if (properties.value().as_string() == "TGA") { newDisplay = new T_racer_Display_TGA(); }
		}
		else if (properties.name() == "ResX") { x = properties.value().as_double(); }
		else if (properties.name() == "ResY") { y = properties.value().as_double(); }
	}

	initFromFile = true;
	newDisplay->init(x, y);
	newDisplay->setDisplayName(name);
	this->setDisplay(newDisplay);
}
