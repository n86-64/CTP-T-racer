#define _USE_MATH_DEFINES
#include <cmath> 
#include <fstream>

#include <jsoncons/json.hpp>

#include "ModelLoader.h"
#include "Display.h"
#include "Scene.h"
#include "helpers/Math_Sampler.h"
#include "helpers/Math_Error.h"

#include "SkeletalMesh.h"

#include "BaseLight.h"


T_racer_Scene::T_racer_Scene()
{}

T_racer_Scene::~T_racer_Scene()
{
	display = nullptr;
	mainCamera = nullptr;
	printf("Exiting."); 
}

void T_racer_Scene::addResourceObject(T_racer_Resource* newRes)
{
	sceneResources.push_back(std::unique_ptr<T_racer_Resource>(newRes));
}

void T_racer_Scene::loadScene(JSONFileReader file)
{
	// Parse succsessful, we can now load the file
	name = file.buffer["SceneName"].as_string();

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

void T_racer_Scene::loadModelAssimp(std::string modelName)
{
	// Load model along with texture and material info. Assign for rendering. 
	T_racer_Resource_SkeletalMesh skeletalMesh;
	if (skeletalMesh.loadSkeletalMesh(modelName, &materials, &textures)) 
	{
		std::vector<Triangle> triangles = skeletalMesh.draw(&materials, &textures); // INEFFICENT - Needs changing. 
		for (Triangle& tri : triangles)
		{
			// Laod the triangles into the scene temporaraly.
			sceneTriangles.emplace_back(tri);
		}
	}
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
	bvh.generateSceneBVH(name, &sceneTriangles);
}


T_racer_TriangleIntersection T_racer_Scene::trace(T_racer_Math::Ray ray)
{
	return bvh.checkForIntersections(&ray);
}

T_racer_TriangleIntersection T_racer_Scene::trace(T_racer_Math::Vector origin, T_racer_Math::Vector direction)
{
	T_racer_Math::Ray ray(origin, direction);
	return bvh.checkForIntersections(&ray);
}

T_racer_TriangleIntersection T_racer_Scene::trace(int x, int y)
{
	T_racer_Math::Ray ray = generateRay(x,  y);
	return bvh.checkForIntersections(&ray);
}

bool T_racer_Scene::visible(T_racer_Math::Vector origin, T_racer_Math::Vector destination)
{
	T_racer_Math::Vector direction = destination - origin;
	float t = direction.normaliseSelfWithMagnitude();
	T_racer_Math::Ray ray(origin, direction);
	return bvh.visible(&ray, t - T_RACER_EPSILON);
}

bool T_racer_Scene::visibleDir(T_racer_Math::Vector origin, T_racer_Math::Vector direction)
{
	T_racer_Math::Ray ray(origin, direction);
	return bvh.visible(&ray, INFINITY);
}

T_racer_Light_Base* T_racer_Scene::retrieveOneLightSource()
{
	// Not adiquite but it will ensure a good light source is selected.
	srand(NULL);
	return sceneLights[rand() % sceneLights.size()].get();
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	// Shirley Method. 
	float theta = mainCamera->getFoV();
	float half_height = tan(theta / 2);
	float half_width = mainCamera->getAspectRatio() * half_height;
	T_racer_Math::Vector origin = mainCamera->getPosition();

	T_racer_Math::Vector w, u, v; 
	mainCamera->getCameraCords(w, u, v);

	T_racer_Math::Vector lower_left_corner(-half_width, -half_height, -1.0f);
	lower_left_corner = origin - u * half_width  - v * half_height - w; 
	T_racer_Math::Vector horizontal =  u * half_width * 2 ;
	T_racer_Math::Vector vertical = v * half_height * 2;

	T_racer_Math::Ray cameraRay = T_racer_Math::Ray(origin, ((lower_left_corner + horizontal * xPos + vertical * yPos) - origin).normalise());

	return cameraRay;
}

T_racer_TriangleIntersection T_racer_Scene::hitsLightSource(T_racer_Math::Ray* ray)
{
	T_racer_TriangleIntersection  returnIntersection; 
	T_racer_TriangleIntersection  intersection;

	for (int i = 0; i < sceneLights.size(); i++) 
	{
		intersection = sceneLights[i]->doesIntersect(ray);
		if (intersection.intersection && intersection.t < returnIntersection.t) 
		{
			returnIntersection = intersection;
		}
	}

	return returnIntersection;
}
