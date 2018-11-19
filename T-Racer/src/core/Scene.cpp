#define _USE_MATH_DEFINES
#include <cmath> 

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
					frameData(x, y, T_racer_Math::Colour(1.0f, 1.0f, 1.0f));
					break;
				}
				else 
				{
					frameData(x, y, T_racer_Math::Colour(0.0f, 0.0f, 0.0f));
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
	// TODO - When generating a ray in the world.

	// Here lets generate a ray. 
	T_racer_Math::Ray     ray;
	T_racer_CameraTransform  camTransform = mainCamera->getCameraTransform();

	//T_racer_Math::Vector rayDir;

/*	T_racer_Math::Vector rasterPos(xPos,yPos);
	T_racer_Math::Matrix4X4 screenTransform = T_racer_Math::createScaleMatrix(T_racer_Math::Vector(display->getWidth(), display->getHeight(), 1.0f)) *
		T_racer_Math::createScaleMatrix(T_racer_Math::Vector(1.0f / display->getWidth(), 1.0f / display->getHeight(), 1.0f)) * 
		T_racer_Math::createTranslationMatrix(T_racer_Math::Vector(-display->getWidth() / 2, -display->getHeight() / 2, 0.0f)); */ // TODO - Add this.
	

	T_racer_Math::Matrix4X4 worldTransform;
	worldTransform = camTransform.projection * camTransform.view;

	worldTransform = T_racer_Math::getInverseMatrix(worldTransform);
	//screenTransform = T_racer_Math::getInverseMatrix(screenTransform);

	////// Here we create the ray. 
	//ray.setPosition(worldTransform * screenTransform * rasterPos);
	//ray.setDirection(ray.getPosition().normalise());
	//rayDir = ray.getDirection();
	//ray.setDirection(rayDir);

//	ray.setMagnitude((mainCamera->getFarZ() - mainCamera->getNearZ()) / ray.getDirection().Z);

	//T_racer_Math::Vector screenPos(
	//	(2 * ((xPos + 0.5)/mainCamera->getWidth()) - 1) * tan(mainCamera->getFoV() / 2 * M_PI / 180) * mainCamera->getAspectRatio(),
	//	(1 - 2 * (yPos/mainCamera->getHeight()) * tan(mainCamera->getFoV() / 2 * M_PI / 180)),
	//	1.0f
	//);

	//screenPos = worldTransform * screenPos;

	//ray.setPosition(mainCamera->getPosition());
	//ray.setDirection((screenPos - ray.getPosition()).normalise());

	float fov = 90.0f;
	float imageAspectRatio = display->getWidth() / display->getHeight(); // assuming width > height 
	float Px = (2 * ((xPos + 0.5) / display->getWidth()) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
	float Py = (1 - 2 * ((yPos + 0.5) / display->getHeight()) * tan(fov / 2 * M_PI / 180));
	T_racer_Math::Vector rayOrigin(0);
	T_racer_Math::Vector  rayDirection = T_racer_Math::Vector(Px, Py, -1); // note that this just equal to Vec3f(Px, Py, -1); 
	
	ray.setPosition(worldTransform * rayOrigin);
	ray.setDirection(((worldTransform * rayDirection) - ray.getPosition()).normalise()); // it's a direction so don't forget to normalize 

	return ray;
}
