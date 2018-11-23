#include "BVHTree.h"

void T_racer_BVH_Tree::generateSceneBVH(std::vector<Triangle>& scenePrimatives)
{
	T_racer_Collider_AABB  aabbBox;
	for (int i = 0; i < scenePrimatives.size(); i++) 
	{
		scenePrimatives[i].generateBoundingBox();
		aabbBox.enlargeBox(*scenePrimatives[i].getCollider());
	}

	// Set the root nodes AABB.
	root->assignBox(aabbBox);


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
