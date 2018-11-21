/** @file ModelLoader.h
*  @brief A simple assimp model loader.
*
*  Loads an assimp model from memory and converts it into an array of triangles. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>

#include "Triangle.h"
#include "core/Resource.h"


class T_racer_ResourceModel : public T_racer_Resource 
{
public:
	T_racer_ResourceModel() = default;

	void loadModel(std::string  pathNames);
	std::vector<Triangle>*  getModelTriangles();



private:
	std::vector<Triangle>  modelTriangles;
};