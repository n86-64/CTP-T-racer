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
	void assignNodes(int newLNode, int newRNode);

	void addPrimativeIndicies(int value);
	void setPrimativeIndicies(std::vector<int>& indicies);
	std::vector<int>& getTriangleIndexList();

	T_racer_Collider_AABB*  getBounds() { return &box; }

	int getLeftNode() const { return lNodeIndex; }
	int getRightNode() const { return rNodeIndex; }

	void addTriangles(T_racer_BVH_CollisionQueue_t* queue);

	// Additional heuristic.
	int getNodeCost() const { return nodeCost; }
	void setNodeCost(float newCost) { nodeCost = newCost; }

	int getNumberOfTriangles() { return triIndex.size(); }
	int getTriangle(int index) { return triIndex[index]; }



private:
	// The box that represents the AABB.
	T_racer_Collider_AABB  box;

	int					   parentIndex = T_RACER_NODE_NULL;
	int					   lNodeIndex = T_RACER_NODE_NULL;
	int					   rNodeIndex = T_RACER_NODE_NULL;

	std::vector<int>       triIndex;

	float				   nodeCost = INFINITY;
};