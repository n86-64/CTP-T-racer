/** @file Renderers.h
*  @brief the base class for all renderer types.
*
*  All renderer systems are to be built on this class.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "Scene.h"
#include "MaterialManager.h"
#include "TextureManager.h"

class T_racer_Renderer_Base 
{
public:
	T_racer_Renderer_Base() = default;

	virtual void Render() = 0;
	void setDisplay(T_racer_Display* newDisplay) { display = newDisplay; }

	void setScene(T_racer_Scene* newScene) { sceneObject = std::unique_ptr<T_racer_Scene>(newScene); 
	sceneObject->setDisplay(display);
	}

protected:
	virtual void tracePath(T_racer_Math::Ray initialRay) = 0;

protected:
	std::unique_ptr<T_racer_Scene>  sceneObject;
	T_racer_MaterialManager         materials;
	T_racer_TextureManager			textures;

	T_racer_Display*				display = nullptr;
};