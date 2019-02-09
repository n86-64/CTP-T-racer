/** @file Mesh.h
*  @brief A mesh object.
*
*  Takes an imported skeletal mesh and loads them up on screen.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include "Resource.h"

#include "helpers/Math_Matrix.h"

// Transform of the mesh. 
struct T_racer_Transform 
{
	T_racer_Math::Matrix4X4 position;
	T_racer_Math::Matrix4X4 rotation;
	T_racer_Math::Matrix4X4 scale;
};


class T_Racer_Resource_Mesh : public T_racer_Resource
{
public:
	T_Racer_Resource_Mesh() = default;

	void loadMesh(std::string name);

	// Gets the triangles for rendering in the scene. 
	void aquireTriangles();

private:
	T_racer_Transform   meshTransform;

	
};