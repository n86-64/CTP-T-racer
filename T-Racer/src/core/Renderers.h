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

class T_racer_Renderer_Base 
{
public:
	T_racer_Renderer_Base() = default;

	virtual void Render() = 0;
	void setDisplay(T_racer_Display* newDisplay) { display = newDisplay; }

protected:
	virtual void tracePath() = 0;

protected:
	std::unique_ptr<T_racer_Scene>  sceneObject;
	T_racer_Display*   display = nullptr;
};