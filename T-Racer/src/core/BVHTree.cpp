#include <queue>
#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 4;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 2;

constexpr float T_RACER_BVH_PARTITION = -1.0f;

//bool triangleSort(Triangle* aAxisVal, Triangle* bAxisVal) 
//{
//	return false;
//}


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
	// root->intersection(ray, &collisionQueue);


}

T_racer_BVH_CollisionQueue_t T_racer_BVH_Tree::getPossibleCollisions()
{
	return collisionQueue;
}

void T_racer_BVH_Tree::createBVHNodes(std::vector<Triangle>& scenePrimatives)
{
	// Implement tree construction here.
	T_racer_BVH_Node* nodePtr = nullptr;
	T_racer_BVH_Node* childL = nullptr;
	T_racer_BVH_Node* childR = nullptr;

	int currentNode = T_RACER_NODE_NULL;
	std::queue<int> nodesToResolve; // The indicies of the nodes we need to resolve.

	nodesToResolve.emplace(0);
	bool generate = false;
	BVHSplitInfo newSplit;

	while (nodesToResolve.size() > 0) 
	{
		// Here we generate the child nodes and add them to the queue.
		nodePtr = &nodes[nodesToResolve.front()];
		newSplit = shouldPartition(nodesToResolve.front(), scenePrimatives);

		if (newSplit.split) 
		{
			// Generate the next child nodes.
			nodes.emplace_back(T_racer_BVH_Node());
			nodes.emplace_back(T_racer_BVH_Node());

			childL = &nodes[nodes.size() - 2];
			childR = &nodes[nodes.size() - 1];

			// Set the boxes and primatives for each.
			nodePtr->assignNodes(nodes.size() - 2, nodes.size() - 1);
			
			nodesToResolve.emplace(nodes.size() - 2);
			nodesToResolve.emplace(nodes.size() - 1);

			// Assign these 
			childL->assignBox(newSplit.lChildBox);
			childR->assignBox(newSplit.rChildBox);
		}


		// Pop the top value of the queue.
		nodesToResolve.pop();
	}
}

float T_racer_BVH_Tree::getSplitCost()
{
	
	return 0.0f;
}

BVHSplitInfo T_racer_BVH_Tree::shouldPartition(int nodeIndex, std::vector<Triangle>& primatives)
{
	BVHSplitInfo  bestCost;
	std::vector<Triangle*>  trianglesToTest;
	trianglesToTest.reserve(nodes[nodeIndex].getTriangleIndexList().size());

	for (int& nodeToTest : nodes[nodeIndex].getTriangleIndexList()) 
	{
		trianglesToTest.emplace_back(&primatives[nodeToTest]);
	}

	
	return bestCost;
}

float T_racer_BVH_Tree::partitionNodeSpace(T_racer_BVH_Node* newNode)
{

	return T_RACER_BVH_PARTITION;
}
