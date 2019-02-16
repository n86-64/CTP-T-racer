/** @file SkeletalMesh.h
*  @brief A Skeletal mesh object that can be drawn.
*
*  Defines a 3D skeleton which is transformed into screen space and rendered.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>
#include <string>

#include "helpers/Math_Matrix.h"

#include "Resource.h"
#include "Triangle.h"

#include "Mesh.h"

struct aiScene;
struct aiNode;

class T_racer_Resource_SkeletalMesh 
{
public:
	T_racer_Resource_SkeletalMesh() = default;

	void loadSkeletalMesh(std::string name);

	std::vector<Triangle>*  getModelTriangles() {};

private:
	void loadMeshesInAssimpScene(const aiScene* scene);
	void loadNodesRecursive(const aiNode* scene, T_racer_Math::Matrix4X4 transform);

private:
	std::string name;

	// Nodes and meshes of the object. 
	std::vector<std::unique_ptr<T_racer_Resource_SkeletalMesh_Mesh>> meshes;

};