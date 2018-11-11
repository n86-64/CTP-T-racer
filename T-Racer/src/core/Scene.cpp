#include "Scene.h"

void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::Render()
{
	// Here we trace the ray for the camera.
}
