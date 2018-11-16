#include "Display.h"
#include "Scene.h"


void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::Render()
{
	T_racer_Math::Ray  ray;
	// Here we trace the ray for the camera.
	
	// Generate a ray for each image in the framebuffer.
	// If intersection with a triangle, colour the pixel else stop. 
	for (int y = 0; y < frameData.height; y++) 
	{
		for (int x = 0; x < frameData.width; x++)
		{
			ray = generateRay(x, y);
			// perform the intersection.
			for (Triangle& triangle : sceneTriangles) 
			{
				if (triangle.isIntersecting(ray).intersection) 
				{
					// Colour the pixel white.
					frameData(x, y, T_racer_Math::Colour(0.0f, 1.0f, 0.0f));
				}
				else 
				{
					frameData(x, y, T_racer_Math::Colour(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}

	display->writeToDisplay(&frameData);
}

void T_racer_Scene::setDisplay(T_racer_Display* newDisplay)
{
	display = newDisplay;
	frameData.setSize(display->getWidth(), display->getHeight());
	mainCamera->setResolution(display->getWidth(), display->getHeight());
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	// Here lets generate a ray. 
	T_racer_Math::Ray     ray;
	T_racer_CameraTransform  camTransform = mainCamera->getCameraTransform();

	T_racer_Math::Vector rasterPos(xPos,yPos);
	T_racer_Math::Matrix4X4 screenTransform; /*= T_racer_Math::createScaleMatrix() *
		T_racer_Math::createScaleMatrix() * 
		T_racer_Math::createTranslationMatrix();*/
	T_racer_Math::Matrix4X4 transform;

	T_racer_Math::Vector cameraPos;
	
	transform = camTransform.projection * camTransform.view;
	transform = T_racer_Math::getInverseMatrix(transform);


	// Here we create the ray. 
	ray.setPosition(transform * screenTransform * cameraPos);
	ray.setDirection(transform * screenTransform * T_racer_Math::forward);
	ray.setMagnitude(mainCamera->getFarZ() - mainCamera->getNearZ());

	return ray;
}
