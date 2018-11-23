/** @file BVHTree.h
*  @brief A basic container for a BVH tree.
*
*  A simple system that generates a BVH tree.
*  Used for optimising Ray Triangle Intersection.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "BVHNode.h"
#include "BVHTests.h"
#include "core/Triangle.h"

class T_racer_BVH_Tree 
{
public:
	T_racer_BVH_Tree() = default;
	~T_racer_BVH_Tree();

	void generateSceneBVH(std::vector<Triangle>& scenePrimatives);
	void checkForIntersections(T_racer_Math::Ray* ray); 

	T_racer_BVH_CollisionQueue_t getPossibleCollisions();

private:
	void createBVHNodes(std::vector<Triangle>& scenePrimatives);

	// Splitting routienes.

private:
	// The root node of the tree.
	T_racer_BVH_Node* root = nullptr;

	// The indicies of the triangles that we have to test.
	T_racer_BVH_CollisionQueue_t  collisionQueue; 

};