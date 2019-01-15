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
#include "Camera.h"
#include "BVHTree.h"

#include "helpers/Image.h"

class T_racer_Display;
class T_racer_Light_Base;

class T_racer_Scene 
{
public:
	T_racer_Scene();

	void addResourceObject(T_racer_Resource* newRes);
	void setMainCamera(T_racer_Camera* newCam) { mainCamera = newCam; };
	
	void loadModel(std::string modelName);

	void addLight(T_racer_Light_Base*  newLight) { sceneLights.emplace_back(newLight); }; // Adds a new light to the scene.

	// Render a single frame and add to a display. 
	void Render();
	void setDisplay(T_racer_Display* newDisplay); 

	// Renderer Routienes
	void setupScene();
	T_racer_BVH_CollisionQueue_t  traceRay(int x, int y); // Returns a list of triangles we have collided with.
	T_racer_BVH_CollisionQueue_t traceRay(T_racer_Math::Vector origin, T_racer_Math::Vector direction); // Returns a proposed intersection with objects in the scene

	int  traceRay2(int x, int y, T_racer_TriangleIntersection& intersectDesc);
	int  traceRay2(T_racer_Math::Vector origin, T_racer_Math::Vector direction, T_racer_TriangleIntersection& intersectDesc);

	Triangle*   getTriangleByIndex(int index) { return &sceneTriangles[index]; }

	T_racer_Light_Base* retrieveOneLightSource();

private:
	std::vector<std::unique_ptr<T_racer_Resource>>  sceneResources;
	std::vector<Triangle>   sceneTriangles;
	std::vector<std::unique_ptr<T_racer_Light_Base>>  sceneLights;

	T_racer_Camera* mainCamera = nullptr;
	T_racer_Display* display;

	Image          frameData;
	
	T_racer_BVH_Tree  bvh;

private:
	T_racer_Math::Ray generateRay(float xPos, float yPos);
};