#include "BVHTree.h"

void T_racer_BVH_Tree::generateSceneBVH(std::vector<Triangle>& scenePrimatives)
{
	T_racer_Math::Vector  worldMin;
	T_racer_Math::Vector  worldMax;

	for (int i = 0; i < scenePrimatives.size(); i++) 
	{
		scenePrimatives[i].generateBoundingBox();
		scenePrimatives[i].getCollider()->getMin();
		scenePrimatives[i].getCollider()->getMax();
	}

	// Set the root nodes AABB.
	
}

void T_racer_BVH_Tree::checkForIntersections(T_racer_Math::Ray* ray)
{
	// Perform the intersection test for the ray.
	root->intersection(ray, &collisionQueue);
}

T_racer_BVH_CollisionQueue_t T_racer_BVH_Tree::getPossibleCollisions()
{
	return collisionQueue;
}
