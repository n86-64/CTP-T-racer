#include "Display.h"
#include "Scene.h"


void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::Render()
{
	// Here we trace the ray for the camera.
	
	// Generate a ray for each image in the framebuffer.
	// If intersection with a triangle, colour the pixel else stop. 
}

void T_racer_Scene::setDisplay(T_racer_Display* newDisplay)
{
	display = newDisplay;
	generateRay(0.0f, 0.0f);
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	// Here lets generate a ray. 
	T_racer_Math::Ray     ray;
	T_racer_CameraTransform  camTransform = mainCamera->getCameraTransform();

	T_racer_Math::Vector screenPos(xPos,yPos);
	T_racer_Math::Vector ndcPos;
	T_racer_Math::Vector cameraSpace;
	T_racer_Math::Matrix4X4  transform;
	
	transform = camTransform.projection * camTransform.view;
	transform = T_racer_Math::getInverseMatrix(transform);

	//ndcPos = T_racer_Math::Vector(screenPos.X + 0.5 / mainCamera->getWidth(), screenPos.Y + 0.5 / mainCamera->getHeight());
	//ndcPos = T_racer_Math::Vector(ndcPos.X * 2 - 1, ndcPos.Y * 2 - 1);

	//cameraSpace = T_racer_Math::Vector()

	// Here we create the ray. 
	ray.setPosition(transform * screenPos);
	ray.setDirection(T_racer_Math::forward);
	ray.setMagnitude(mainCamera->getFarZ() - mainCamera->getNearZ());

	return ray;
}
