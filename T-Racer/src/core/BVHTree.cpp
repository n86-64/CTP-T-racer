#include <queue>
#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
// Constants derived from PBRT 3rd edition (p.g. 207)
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 1;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 80;


constexpr float T_RACER_BVH_PARTITION = -1.0f;

bool triangleSort(BVHEdge a, BVHEdge b) 
{
	return (a.t < b.t);
}


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

	// int currentNode = T_RACER_NODE_NULL;
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

			// Assign these there chosen bounding boxes.
			childL->assignBox(newSplit.lChildBox);
			childR->assignBox(newSplit.rChildBox);

			// Assign primative indexes to each.

		}


		// Pop the top value of the queue.
		nodesToResolve.pop();
	}
}


void T_racer_BVH_Tree::getSplitCost
(
	BVHSplitInfo& splitInfo, 
	std::vector<Triangle*>& nodePrimatives, 
	std::vector<int>& primativeIDs, 
	float totalSA
)
{
	float currentCost = 0.0f;
	float bestCost = INFINITY;
	int   bestEdge = -1;
	float invSA = 1 / totalSA;

	std::vector<BVHEdge>  edges;
	edges.reserve(primativeIDs.size());
	BVHEdge  newEdge;

	// Create each of the edges based on the axis and the boxes.
	// Project onto the axis we are checking and then sort in order.
	for (int i = 0; i < primativeIDs.size(); i++) 
	{
		newEdge.primativeRef = primativeIDs[i];
		newEdge.t = nodePrimatives[primativeIDs[i]]->getCollider()->getMin().values[splitInfo.axis];
		edges.emplace_back(newEdge);

		newEdge.primativeRef = primativeIDs[i];
		newEdge.t = nodePrimatives[primativeIDs[i]]->getCollider()->getMax().values[splitInfo.axis];
		edges.emplace_back(newEdge);
	}
	std::sort(edges.begin(), edges.end(), triangleSort);

	// Calculate the cost of a split at this point.

}

BVHSplitInfo T_racer_BVH_Tree::shouldPartition(int nodeIndex, std::vector<Triangle>& primatives)
{
	float surfaceArea = nodes[nodeIndex].getBounds()->getSurfaceArea();
	BVHSplitInfo  bestCost;
	BVHSplitInfo  currentCost;
	bestCost.splitCost = INFINITY;  // This should hold true if no good splits are found.
	bestCost.axis = -1;

	std::vector<Triangle*>  trianglesToTest;
	std::vector<BVHEdge>	edges;

	trianglesToTest.reserve(nodes[nodeIndex].getTriangleIndexList().size());
	edges.reserve(nodes[nodeIndex].getTriangleIndexList().size() * 2);

	for (int& nodeToTest : nodes[nodeIndex].getTriangleIndexList()) 
	{
		trianglesToTest.emplace_back(&primatives[nodeToTest]);
	}

	// for each axis we perform the SAH test.
	for (int i = 0; i < 3; i++) 
	{
		currentCost.axis = i;
		getSplitCost(currentCost, trianglesToTest, nodes[nodeIndex].getTriangleIndexList(), surfaceArea);

		if (currentCost.splitCost < bestCost.splitCost)
		{
			bestCost = currentCost;
		}
	}
	
	// Here we create the boxes and assign the primatives.



	return bestCost;
}

// DEPRICATED!!!
float T_racer_BVH_Tree::partitionNodeSpace(T_racer_BVH_Node* newNode)
{

	return T_RACER_BVH_PARTITION;
}
