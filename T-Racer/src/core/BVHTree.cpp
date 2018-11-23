#include <queue>
#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 4;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 1;


T_racer_BVH_Tree::~T_racer_BVH_Tree()
{
	if (root) 
	{ 
		delete root; 
		root = nullptr; 
	}
}

void T_racer_BVH_Tree::generateSceneBVH(std::vector<Triangle>& scenePrimatives)
{
	T_racer_Collider_AABB  aabbBox;
	if (root) { delete root; root = nullptr; }
	root = new T_racer_BVH_Node();

	for (int i = 0; i < scenePrimatives.size(); i++) 
	{
		scenePrimatives[i].generateBoundingBox();
		root->addPrimativeIndicies(i);
		aabbBox.enlargeBox(*scenePrimatives[i].getCollider());
	}

	// Set the root nodes AABB.
	root->assignBox(aabbBox);
	createBVHNodes(scenePrimatives);
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

void T_racer_BVH_Tree::createBVHNodes(std::vector<Triangle>& scenePrimatives)
{
	// Implement tree construction here.
	T_racer_BVH_Node* currentNode = nullptr;
	std::queue<T_racer_BVH_Node*> nodesToResolve;
	nodesToResolve.emplace(root);
	bool generate = false;

	while (nodesToResolve.size() > 0) 
	{
		// Here we generate the child nodes and add them to the queue.
		if (!generate) 
		{

			generate = true;
		}
	}
}
