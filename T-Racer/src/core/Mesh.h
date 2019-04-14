/** @file Mesh.h
*  @brief A Component of a skeletal mesh that can be drawn.
*
*  Defines a mesh which forms part of a skeletal mesh.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>

#include <assimp/mesh.h>

#include "Vertex.h"
#include "helpers/Math_Matrix.h"

class T_racer_Resource_SkeletalMesh_Mesh 
{
public:
	T_racer_Resource_SkeletalMesh_Mesh() = default;
	T_racer_Resource_SkeletalMesh_Mesh(aiMesh* newMesh);

	// Verticies and indicies
	std::vector<int>					modelIndicies;
	std::vector<T_racer_Vertex>			modelVerticies;

	int materialID = 0;
};