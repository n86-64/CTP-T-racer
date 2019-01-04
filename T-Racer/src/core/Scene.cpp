#define _USE_MATH_DEFINES
#include <cmath> 

#include "ModelLoader.h"
#include "Display.h"
#include "Scene.h"


void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::loadModel(std::string modelName)
{
	T_racer_ResourceModel  model;
	model.loadModel(modelName);
	std::vector<Triangle>* triangles = model.getModelTriangles();

	for (Triangle& tri : *triangles) 
	{
		// Laod the triangles into the scene temporaraly.
		sceneTriangles.emplace_back(tri);
	}
}

void T_racer_Scene::Render()
{
	bvh.generateSceneBVH(&sceneTriangles);

	T_racer_Math::Ray  ray;
	// Here we trace the ray for the camera.
	
	// Generate a ray for each image in the framebuffer.
	// If intersection with a triangle, colour the pixel else stop. 
	for (int y = 0; y < frameData.height; y++) 
	{
		for (int x = 0; x < frameData.width; x++)
		{
			ray = generateRay(x, y);
			bvh.checkForIntersections(&ray);

			// perform the intersection.
			// Based on results from the BVH.
			//for (Triangle& triangle : sceneTriangles) 
			//{

			for (int pIndex : bvh.getPossibleCollisions().triangleIndexes) 
			{
				if (sceneTriangles[pIndex].isIntersecting(ray).intersection)
				{
					// Add the data to the ray here.

					// Colour the pixel white.
					frameData(x, y, T_racer_Math::Colour(1.0f, 1.0f, 1.0f));
					break;
				}
				else
				{
					frameData(x, y, T_racer_Math::Colour(0.0f, 0.0f, 0.0f));
				}
			}

			//}
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

void T_racer_Scene::setupScene()
{
	// Setup the scene for rendering.
	bvh.generateSceneBVH(&sceneTriangles);
}

T_racer_BVH_CollisionQueue_t T_racer_Scene::traceRay(int x, int y)
{
	T_racer_BVH_CollisionQueue_t collisions;
	collisions.ray = generateRay(x, y);
	bvh.checkForIntersections(&collisions.ray);
	collisions.triangleIndexes = bvh.getPossibleCollisions().triangleIndexes;

	return collisions;
}

T_racer_BVH_CollisionQueue_t T_racer_Scene::traceRay(T_racer_Math::Vector origin, T_racer_Math::Vector direction)
{
	T_racer_BVH_CollisionQueue_t collisions;
	collisions.ray.setPosition(origin);
	collisions.ray.setDirection(direction);
	bvh.checkForIntersections(&collisions.ray);

	collisions.triangleIndexes = bvh.getPossibleCollisions().triangleIndexes;

	return collisions;
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	// Here lets generate a ray. 
	T_racer_Math::Ray     ray;
	T_racer_CameraTransform  camTransform = mainCamera->getCameraTransform();

	T_racer_Math::Matrix4X4 worldTransform = /*camTransform.projection **/ camTransform.view;
	worldTransform = T_racer_Math::getInverseMatrix(worldTransform);

	float imageAspectRatio = mainCamera->getAspectRatio();
	float Px = (2 * ((xPos + 0.5) / display->getWidth()) - 1) * tan(mainCamera->getFoV() / 2) * imageAspectRatio;
	float Py = (1 - 2 * ((yPos + 0.5) / display->getHeight()) * tan(mainCamera->getFoV() / 2));

	T_racer_Math::Vector rayOrigin = mainCamera->getPosition();
	T_racer_Math::Vector  rayDirection = T_racer_Math::Vector(Px, Py,  mainCamera->getForward().Z);
	
	ray.setPosition(worldTransform * rayOrigin);
	ray.setDirection(((worldTransform * rayDirection) - ray.getPosition()).normalise()); // it's a direction so don't forget to normalize 

	return ray;
}
