/** @file Scene.h
*  @brief A 3D pathtracing scene.
*
*  Defines a scene which is a collection of 3D objects, lights and camera.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <memory>
#include <vector>

#include "Resource.h"
#include "Camera.h"


class T_racer_Scene 
{
public:
	T_racer_Scene() = default;

	void addResourceObject(T_racer_Resource* newRes);
	void setMainCamera(T_racer_Camera* newCam) { mainCamera = newCam; };
	

	// Render a single frame and add to a display. 
	void Render();

private:
	std::vector<std::unique_ptr<T_racer_Resource>>  sceneResources;
	T_racer_Camera* mainCamera = nullptr;


private:
	void traceRay();
};