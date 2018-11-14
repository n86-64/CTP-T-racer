#include "Display.h"
#include "Scene.h"


void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::Render()
{
	// Here we trace the ray for the camera.
	
}

void T_racer_Scene::setDisplay(T_racer_Display* newDisplay)
{
	display = newDisplay;
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	// Here lets generate a ray. 
	T_racer_Math::Vector screenPos(xPos,yPos);

	T_racer_Math::Matrix4X4  world;


	return T_racer_Math::Ray();
}
