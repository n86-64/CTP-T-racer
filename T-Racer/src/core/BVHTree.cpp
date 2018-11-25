#include <queue>
#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
// Constants derived from PBRT 3rd edition (p.g. 207)
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 1;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 80;


constexpr float T_RACER_BVH_PARTITION = -1.0f;

// Predicate for sorting triangles along an axis.
bool triangleSort(BVHEdge a, BVHEdge b) 
{
	return (a.t < b.t);
}


T_racer_BVH_Tree::~T_racer_BVH_Tree()
{
	//if (root) 
	//{ 
	//	delete root; 
	//	root = nullptr; 
	//}
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

	std::queue<int> nodesToCheck;
	nodesToCheck.emplace(0);
	T_racer_BVH_Node* currentNode = nullptr;

	while (nodesToCheck.size() > 0) 
	{
		currentNode = &nodes[nodesToCheck.front()];

		if (currentNode->getBounds()->isIntersected(*ray)) 
		{
			if (currentNode->getLeftNode() != T_RACER_NODE_NULL &&
				currentNode->getRightNode() != T_RACER_NODE_NULL)
			{
				nodesToCheck.emplace(currentNode->getLeftNode());
				nodesToCheck.emplace(currentNode->getRightNode());
			}
			else 
			{
				// its a leaf we dont need to check this anymore.
				currentNode->addTriangles(&collisionQueue);
			}
		}

		nodesToCheck.pop();
	}
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

			// Assign these there chosen bounding boxes.
			childL->assignBox(newSplit.lChildBox);
			childR->assignBox(newSplit.rChildBox);

			// Assign primative indexes to each of the children based on intersections.
			// Then we emplace nodes and calculate more splits.



			nodesToResolve.emplace(nodes.size() - 2);
			nodesToResolve.emplace(nodes.size() - 1);
		}


		// Pop the top value of the queue.
		nodesToResolve.pop();
	}
}


void T_racer_BVH_Tree::getSplitCost
(
	int nodeIndex,
	BVHSplitInfo& splitInfo, 
	std::vector<Triangle*>& nodePrimatives, 
	std::vector<int>& primativeIDs, 
	float totalSA
)
{
	int aPrimCount = 0;
	int bPrimCount = primativeIDs.size();

	float currentCost = 0.0f;
	float bestCost = INFINITY;
	int   bestEdge = -1;
	float invSA = 1 / totalSA;

	std::vector<BVHEdge>  edges;
	edges.reserve(2 * primativeIDs.size());
	BVHEdge  newEdge;

	// Create each of the edges based on the axis and the boxes.
	// Project onto the axis we are checking and then sort in order.
	for (int i = 0; i < primativeIDs.size(); i++) 
	{
		newEdge.primativeRef = primativeIDs[i];
		newEdge.t = nodePrimatives[primativeIDs[i]]->getCollider()->getMin().values[splitInfo.axis];
		newEdge.startNode = true;
		edges.emplace_back(newEdge);

		newEdge.primativeRef = primativeIDs[i];
		newEdge.t = nodePrimatives[primativeIDs[i]]->getCollider()->getMax().values[splitInfo.axis];
		newEdge.startNode = false;
		edges.emplace_back(newEdge);
	}
	std::sort(edges.begin(), edges.end(), triangleSort);

	T_racer_Collider_AABB  leftAABB;
	T_racer_Collider_AABB  rightAABB;

	T_racer_Math::Vector   leftMax;
	T_racer_Math::Vector   rightMin;

	// Calculate the cost of a split at this point.
	for (int j = 0; j < edges.size(); j++) 
	{
		leftMax = nodes[nodeIndex].getBounds()->getMax();
		leftMax.values[splitInfo.axis] = edges[j].t;

		rightMin = nodes[nodeIndex].getBounds()->getMin();
		rightMin.values[splitInfo.axis] = edges[j].t;

		leftAABB.resizeBox(nodes[nodeIndex].getBounds()->getMin(), leftMax);
		rightAABB.resizeBox(rightMin, nodes[nodeIndex].getBounds()->getMax());

		if (!edges[j].startNode)
		{
			bPrimCount--;
		}

		// Create bounding boxes getting there surface area.
		if (edges[j].t > nodes[nodeIndex].getBounds()->getMin().values[splitInfo.axis] &&
			edges[j].t < nodes[nodeIndex].getBounds()->getMax().values[splitInfo.axis]) 
		{
			// calculate cost of intersection for each edge getting the best one.
			currentCost = T_RACER_BVH_COST_TRAVERSAL_NODES
				+ (getGeometricProbibility(leftAABB, invSA) * (T_RACER_BVH_COST_INTERSECTION_TRIANGLE * aPrimCount))
				+ (getGeometricProbibility(rightAABB, invSA) * (T_RACER_BVH_COST_INTERSECTION_TRIANGLE * bPrimCount));

			if (currentCost < bestCost) 
			{
				bestCost = currentCost;
				bestEdge = j;
				splitInfo.lChildBox = leftAABB;
				splitInfo.rChildBox = rightAABB;
			}
		}

		if(edges[j].startNode)
		{
			aPrimCount++;
		}
	}

	splitInfo.splitCost = bestCost;
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
		getSplitCost(nodeIndex, currentCost, trianglesToTest, nodes[nodeIndex].getTriangleIndexList(), surfaceArea);

		if (currentCost.splitCost < bestCost.splitCost)
		{
			bestCost = currentCost;
		}
	}

	// Should we split.
	// If so generate the boxes used from splitting.
	// else just set to false.


	return bestCost;
}

float T_racer_BVH_Tree::getGeometricProbibility(T_racer_Collider_AABB& col, float invSurfaceArea)
{
	return col.getSurfaceArea() * invSurfaceArea;
}

// DEPRICATED!!!
float T_racer_BVH_Tree::partitionNodeSpace(T_racer_BVH_Node* newNode)
{

	return T_RACER_BVH_PARTITION;
}
