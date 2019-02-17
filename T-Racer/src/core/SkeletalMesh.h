/** @file SkeletalMesh.h
*  @brief A Skeletal mesh object that can be drawn.
*
*  Defines a 3D skeleton which is transformed into screen space and rendered.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <string>

#include "Resource.h"
#include "Triangle.h"

#include "Mesh.h"
#include "MeshNode.h"

struct aiScene;
struct aiNode;

class T_racer_Resource_SkeletalMesh 
{
public:
	T_racer_Resource_SkeletalMesh() = default;

	void loadSkeletalMesh(std::string name);

	std::vector<Triangle>  draw();

private:
	void loadMeshesInAssimpScene(const aiScene* scene);
	void loadNodesRecursive(const aiNode* scene, T_racer_Math::Matrix4X4 transform, int parent);

private:
	std::string name;

	// Nodes and meshes of the object. 
	std::vector<T_racer_Resource_SkeletalMesh_Mesh>					meshes;
	std::vector<T_racer_Resource_SkeletalMesh_Node>					 nodes;

};