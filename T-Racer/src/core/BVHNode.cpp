#include "BVHTests.h"
#include "BVHNode.h"

void T_racer_BVH_Node::createBox(T_racer_Math::Vector min, T_racer_Math::Vector max)
{
	// Create a box in world space to these specified points. 
	box = T_racer_Collider_AABB(min, max);
}

void T_racer_BVH_Node::intersection(T_racer_Math::Ray* ray, T_racer_BVH_CollisionQueue_t* queue)
{
	// TODO - Does this box intersect with a ray. If so we should look at checking our children.
	// or if there are no children we return the index of the triangles here in the box.
	if (box.isIntersected(*ray)) 
	{
		if (!lNode && !rNode) 
		{
			lNode->intersection(ray, queue);
			rNode->intersection(ray, queue);
		}
		else 
		{
			addTriangles(queue);
		}
	}
}

void T_racer_BVH_Node::assignNodes(T_racer_BVH_Node* newLeft, T_racer_BVH_Node* newRight)
{
	lNode = newLeft;
	rNode = newRight;
}

void T_racer_BVH_Node::addTriangles(T_racer_BVH_CollisionQueue_t* queue)
{
	// Add the triangles that we want to test. 
	for (int& index : triIndex) 
	{
		queue->triangleIndexes.emplace_back(index);
	}
}
