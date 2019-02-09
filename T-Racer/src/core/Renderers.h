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
	virtual ~T_racer_Renderer_Base() = default;

	virtual void Render() = 0;
	void setDisplay(T_racer_Display* newDisplay);/* { display = newDisplay; }*/

	void setScene(T_racer_Scene* newScene) 
	{ 
		sceneObject = newScene; sceneObject->setDisplay(display); 	
		sceneObject->materials.retrieveMaterial(0)->setTexture(sceneObject->textures.createTexture("default"));
	}

	virtual void renderThreaded() = 0; // Threaded path.

protected:

	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance) = 0;
	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath) = 0;

protected:
	T_racer_Scene*						sceneObject;

	T_racer_Display*					display = nullptr;

	// Used for tile rendering.
	std::atomic<int>					currentTile = 0;
	std::atomic<int>					compleatedTiles = 0;

	int									tileCount = 0;
	int									threadCount = 0;
	T_racer_Math::Vector				tileSize = T_racer_Math::Vector(INFINITY, INFINITY);
	std::vector<std::thread>			tileThreads; 
};