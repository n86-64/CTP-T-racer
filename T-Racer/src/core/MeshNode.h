/** @file MeshNode.h
*  @brief A Node of an Object.
*
*  Stores transform information for meshes that are being rendered.
*  Used in the transform process for rendering meshes.
*
*  Derived from assimp implimentation for Advanced Technology Task-3.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include <vector>

#include "helpers/Math_Matrix.h"


class T_racer_Resource_SkeletalMesh_Node 
{
public:
	T_racer_Resource_SkeletalMesh_Node() = default;

	void assignMeshes(int newMesh);

	void setMeshSize(int nMeshes) { meshIndicies.reserve(nMeshes); }

	void setModelMatrix(T_racer_Math::Matrix4X4& mat) { modelMatrix = mat; }
	T_racer_Math::Matrix4X4 getModelMatrix() { return modelMatrix; }

	void setParent(int pIndex) { parent = pIndex; }
	void addChild(int cIndex) { children.emplace_back(cIndex); }

	std::vector<int>& getModelIndicies() { return meshIndicies; }
	std::vector<int>& getChildren() { return children; }

private:
	T_racer_Math::Matrix4X4							modelMatrix;

	int				      							parent;
	std::vector<int>								children;
	std::vector<int>								meshIndicies;
};