/** @file BVHNode.h
*  @brief A BVH tree node.
*
*  BVH Nodes are represeted by AABB boxes in the scene. These are then checked within a BVH tree.
*  This allows intersection to be accelerated quickly.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include <vector>

#include "AABB.h"

constexpr int T_RACER_NODE_NULL = -1;

struct  T_racer_BVH_CollisionQueue_t;

class T_racer_BVH_Node 
{
public:
	T_racer_BVH_Node() = default;
	~T_racer_BVH_Node();

	// Defines the nodes AABB box.
	void createBox(T_racer_Math::Vector min, T_racer_Math::Vector max);

	void assignBox(T_racer_Collider_AABB& nBox);

	// Perform an Intersection Test with a ray.
	void intersection(T_racer_Math::Ray* ray, T_racer_BVH_CollisionQueue_t* queue);

	// Give this node some children. 
	void assignNodes(T_racer_BVH_Node* newLeft, T_racer_BVH_Node* newRight);
	void assignNodes(int newLNode, int newRNode);

	void addPrimativeIndicies(int value);
	std::vector<int>& getTriangleIndexList();

	void clearChildNodes();

	T_racer_Collider_AABB*  getBounds() { return &box; }

	int getLeftNode() const { return lNodeIndex; }
	int getRightNode() const { return rNodeIndex; }

	void addTriangles(T_racer_BVH_CollisionQueue_t* queue);

private:
	// The box that represents the AABB.
	T_racer_Collider_AABB  box;

	// DEPRECATED!!!
	T_racer_BVH_Node*      parent = nullptr;
	T_racer_BVH_Node*      lNode = nullptr;
	T_racer_BVH_Node*      rNode = nullptr;

	int					   parentIndex = T_RACER_NODE_NULL;
	int					   lNodeIndex = T_RACER_NODE_NULL;
	int					   rNodeIndex = T_RACER_NODE_NULL;

	std::vector<int>       triIndex;
};