/** @file Renderers.h
*  @brief the base class for all renderer types.
*
*  All renderer systems are to be built on this class.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <thread>
#include <mutex>
#include <atomic>

#include "Scene.h"
#include "BaseLight.h"
#include "Display.h"

class T_racer_Renderer_Base 
{
public:
	T_racer_Renderer_Base() = default;
	virtual ~T_racer_Renderer_Base();

	virtual void Render() = 0;
	void setDisplay(T_racer_Display* newDisplay);
	void setDisplay(JSONFileReader displayName);

	void setScene(T_racer_Scene* newScene) 
	{ 
		sceneObject = newScene; sceneObject->setDisplay(display); 	
		sceneObject->materials.retrieveMaterial(0)->setTexture(sceneObject->textures.createTexture("default"));
	}

	virtual void renderThreaded() = 0; // Threaded path.

	virtual void postDisplayUpdate() {};

protected:
	T_racer_Scene*						sceneObject;

	T_racer_Display*					display = nullptr;

	// Used for tile rendering.
	std::atomic<int>					currentTile = 0;
	std::atomic<int>					compleatedTiles = 0;
	std::atomic<int>					sampleCount = 1;

	int									tileCount = 0;
	int									threadCount = 0;
	T_racer_Math::Vector				tileSize = T_racer_Math::Vector(INFINITY, INFINITY);
	std::vector<std::thread>			tileThreads; 

	bool								initFromFile = false;
};