#include "BVHTests.h"
#include "BVHNode.h"

T_racer_BVH_Node::~T_racer_BVH_Node()
{
}

void T_racer_BVH_Node::createBox(T_racer_Math::Vector min, T_racer_Math::Vector max)
{
	// Create a box in world space to these specified points. 
	box = T_racer_Collider_AABB(min, max);
}

void T_racer_BVH_Node::assignBox(T_racer_Collider_AABB & nBox)
{
	box = nBox;
}

void T_racer_BVH_Node::assignNodes(int newLNode, int newRNode)
{
	lNodeIndex = newLNode;
	rNodeIndex = newRNode;
}

void T_racer_BVH_Node::addPrimativeIndicies(int value)
{
	// TODO - Add code to prevent the addition of duplicate triangle veritices.
	triIndex.emplace_back(value);
}

std::vector<int>& T_racer_BVH_Node::getTriangleIndexList()
{
	return triIndex;
}

void T_racer_BVH_Node::addTriangles(T_racer_BVH_CollisionQueue_t* queue)
{
	// Add the triangles that we want to test. 
	for (int& index : triIndex) 
	{
		queue->triangleIndexes.emplace_back(index);
	}
}
