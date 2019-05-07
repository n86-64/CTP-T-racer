#define _USE_MATH_DEFINES
#include <cmath> 
#include <fstream>

#include "ModelLoader.h"
#include "Display.h"
#include "Scene.h"

#include "helpers/Utility.h"
#include "helpers/Math_Sampler.h"
#include "helpers/Math_Error.h"

#include "SkeletalMesh.h"

#include "PointLight.h"
#include "AreaLight.h"

T_racer_Scene::T_racer_Scene()
{
	T_RACER_RELEASE_RESOURCE((void*&)mainCamera);
}

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
	std::string type;

	// Parse succsessful, we can now load the file
	name = file.buffer["SceneName"].as_string();
	
	for (auto& member : file.buffer.members()) 
	{
		if (member.name() != "SceneName") 
		{
			if (member.value()["Type"].as_string() == "Light")
			{
				T_racer_Light_Base* newLight = nullptr;
				if (member.value()["LightType"].as_string() == "Point")
				{
					newLight = new T_racer_Light_Point();
				}
				else if (member.value()["LightType"].as_string() == "Area")
				{
					newLight = new T_racer_Light_Area();
				}

				newLight->init(member);
				addLight(newLight);
			}
			else if (member.value()["Type"].as_string() == "Mesh")
			{
				// Here we load a mesh.
				loadModelAssimp("resources/" + member.value()["MeshName"].as_string(), member.value()["Mesh Material"].as_string(), member.value()["Texture"].as_string());
			}
			else if (member.value()["Type"].as_string() == "Camera") 
			{
				mainCamera = new T_racer_Camera();
				mainCamera->init(member);
			}
		}
	}
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

void T_racer_Scene::loadModelAssimp(std::string modelName, std::string matType, std::string overrideTexture)
{
	// Load model along with texture and material info. Assign for rendering. 
	T_racer_Resource_SkeletalMesh skeletalMesh;
	if (skeletalMesh.loadSkeletalMesh(modelName, &materials, &textures, matType, overrideTexture)) 
	{
		std::vector<Triangle> triangles = skeletalMesh.draw(&materials, &textures, overrideTexture); // INEFFICENT - Needs changing. 
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
	mainCamera->setupCamera();
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

T_racer_Light_Base* T_racer_Scene::retrieveOneLightSource(T_racer_Math::Sampler* sampler)
{
	// Not adiquite but it will ensure a good light source is selected.
	//srand(NULL);
	return sceneLights[sampler->RandomRange(0, sceneLights.size() - 1)].get();
}

T_racer_Light_Base * T_racer_Scene::retrieveOneLightSource(T_racer_Math::Sampler* sampler, int& lightIndex)
{
	//srand(NULL);
	lightIndex = sampler->RandomRange(0, sceneLights.size() - 1);
	return sceneLights[lightIndex].get();
}

T_racer_Math::Ray T_racer_Scene::generateRay(float xPos, float yPos)
{
	T_racer_Math::Vector  camPos = mainCamera->getPosition();
	T_racer_Math::Ray cameraRay = T_racer_Math::Ray(camPos, ((mainCamera->lower_left_corner + (mainCamera->horizontal * xPos) + (mainCamera->vertical * yPos)) - camPos).normalise());

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
			returnIntersection.lightID = i;
		}
	}

	return returnIntersection;
}
