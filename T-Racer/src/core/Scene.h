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
#include "Triangle.h"
#include "MaterialManager.h"
#include "TextureManager.h"
#include "Camera.h"
#include "BVHTree.h"

#include "helpers/Image.h"

#include "helpers/JSONFileParser.h"


class T_racer_Display;
class T_racer_Light_Base;

class T_racer_Scene 
{
public:
	T_racer_Scene();
	~T_racer_Scene();

	void addResourceObject(T_racer_Resource* newRes);
	void setMainCamera(T_racer_Camera* newCam) { mainCamera = newCam; };
	
	void loadScene(JSONFileReader file);

	std::string getName() { return name; }
	void setName(std::string sceneName) { name = sceneName; }

	void loadModel(std::string modelName);
	void loadModelAssimp(std::string modelName, std::string matType, std::string overrideTexture);

	void addLight(T_racer_Light_Base*  newLight) { sceneLights.emplace_back(newLight); } // Adds a new light to the scene.
	float getProbabilityDensityLightSourceSelection() { return 1.0f / sceneLights.size(); }

	// Render a single frame and add to a display. 
	void setDisplay(T_racer_Display* newDisplay); 

	T_racer_Camera* getMainCamera() { return mainCamera; }

	// Renderer Routienes
	void setupScene();

	T_racer_TriangleIntersection trace(T_racer_Math::Ray ray);
	T_racer_TriangleIntersection trace(int x, int y);
	T_racer_TriangleIntersection trace(T_racer_Math::Vector origin, T_racer_Math::Vector direction);
	bool visible(T_racer_Math::Vector origin, T_racer_Math::Vector destination);
	bool visibleDir(T_racer_Math::Vector origin, T_racer_Math::Vector direction);

	Triangle*   getTriangleByIndex(int index) { return &sceneTriangles[index]; }

	T_racer_Light_Base* retrieveOneLightSource(T_racer_Math::Sampler* sampler);
	T_racer_Light_Base* retrieveOneLightSource(T_racer_Math::Sampler* sampler, int& lightIndex);
	T_racer_Light_Base* retrieveLightByIndex(int i) { return sceneLights[i].get(); }

	T_racer_Math::Ray generateRay(float xPos, float yPos);

	T_racer_TriangleIntersection  hitsLightSource(T_racer_Math::Ray* ray);

public:
	// Manager objects which are acsessable properties. 
	T_racer_MaterialManager				materials;
	T_racer_TextureManager				textures;

	T_racer_Camera* mainCamera = nullptr;

private:
	std::string											name = "NULLScene"; 
	std::vector<std::unique_ptr<T_racer_Resource>>		sceneResources;
	std::vector<Triangle>								sceneTriangles;
	std::vector<std::unique_ptr<T_racer_Light_Base>>	sceneLights;

	T_racer_Display* display;

	Image          frameData;
	
	T_racer_BVH_Tree  bvh;
};