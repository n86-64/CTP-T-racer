#include <queue>
#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
// Constants derived from PBRT 3rd edition (p.g. 207)
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 1;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 80;

constexpr int T_RACER_BVH_TRIANGLE_MAX_QUOTA = 2;


constexpr float T_RACER_BVH_PARTITION = -1.0f;

// Predicate for sorting triangles along an axis.
bool triangleSort(BVHEdge a, BVHEdge b) 
{
	return (a.t < b.t);
}

bool primativeSort(BVHPrimative& a, BVHPrimative& b) 
{
	return (*a.triangles)[a.primativeID].getCollider().getBoxMidpoint().values[a.axis] < (*b.triangles)[b.primativeID].getCollider().getBoxMidpoint().values[b.axis];
}

T_racer_BVH_Tree::~T_racer_BVH_Tree()
{

}

void T_racer_BVH_Tree::generateSceneBVH(std::vector<Triangle>* scenePrimatives)
{
	sceneObjects = scenePrimatives;
	T_racer_Collider_AABB  aabbBox;
	for (int i = 0; i < scenePrimatives->size(); i++) 
	{
		(*sceneObjects)[i].generateBoundingBox();
		nodes[0].addPrimativeIndicies(i);
		aabbBox.enlargeBox((*sceneObjects)[i].getCollider());
	}

	// Set the root nodes AABB.
	nodes[0].assignBox(aabbBox);
	createBVHNodes();
}

void T_racer_BVH_Tree::checkForIntersections(T_racer_Math::Ray* ray)
{
	// Perform the intersection test for the ray.
	// root->intersection(ray, &collisionQueue);
	collisionQueue.triangleIndexes.clear();
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

void T_racer_BVH_Tree::createBVHNodes()
{
	// Implement tree construction here.
	T_racer_BVH_Node* childL = nullptr;
	T_racer_BVH_Node* childR = nullptr;

	// int currentNode = T_RACER_NODE_NULL;
	std::queue<int> nodesToResolve; // The indicies of the nodes we need to resolve.
	nodesToResolve.emplace(0);
	BVHSplitInfo newSplit;

	while (nodesToResolve.size() > 0) 
	{
		// Here we generate the child nodes and add them to the queue.
		newSplit = shouldPartition(nodesToResolve.front());

		if (newSplit.split) 
		{
			// Generate the next child nodes.
			nodes.emplace_back(T_racer_BVH_Node());
			nodes.emplace_back(T_racer_BVH_Node());

			childL = &nodes[nodes.size() - 2];
			childR = &nodes[nodes.size() - 1];

			// Set the boxes and primatives for each.
			nodes[nodesToResolve.front()].assignNodes((int)nodes.size() - 2, (int)nodes.size() - 1);

			// Assign these there chosen bounding boxes.
			childL->assignBox(newSplit.lChildBox);
			childR->assignBox(newSplit.rChildBox);

			//std::vector<int> primatives = nodes[nodesToResolve.front()].getTriangleIndexList();
			//for (int i = 0; i < primatives.size(); i++) 
			//{
			//	if (childL->getBounds()->getMin().values[newSplit.axis] < (*sceneObjects)[primatives[i]].getCollider().getMax().values[newSplit.axis] &&
			//		childL->getBounds()->getMax().values[newSplit.axis] > (*sceneObjects)[primatives[i]].getCollider().getMin().values[newSplit.axis])
			//	{
			//		childL->addPrimativeIndicies(primatives[i]);
			//	}
			//	
			//	if (childR->getBounds()->getMin().values[newSplit.axis] < (*sceneObjects)[primatives[i]].getCollider().getMax().values[newSplit.axis] &&
			//		childR->getBounds()->getMax().values[newSplit.axis] > (*sceneObjects)[primatives[i]].getCollider().getMin().values[newSplit.axis])
			//	{
			//		childR->addPrimativeIndicies(primatives[i]);
			//	}
			//}


			childL->setPrimativeIndicies(newSplit.lPrims);
			childR->setPrimativeIndicies(newSplit.rPrims);



			// Assign primative indexes to each of the children based on intersections.
			// Then we emplace nodes and calculate more splits.
			//for (int i = 0; i < nodes[nodesToResolve.front()].getTriangleIndexList(); i++) 
			//{
			//	if (childL->getBounds()->getMin().values[newSplit.axis] < newSplit.edges[i].t &&
			//		childL->getBounds()->getMax().values[newSplit.axis] > newSplit.edges[i].t)
			//	{
			//		childL->addPrimativeIndicies(newSplit.edges[i].primativeRef);
			//	}

			//	if(childR->getBounds()->getMin().values[newSplit.axis] < newSplit.edges[i].t &&
			//		childR->getBounds()->getMax().values[newSplit.axis] > newSplit.edges[i].t)
			//	{
			//		childR->addPrimativeIndicies(newSplit.edges[i].primativeRef);
			//	}
			//}

			nodesToResolve.emplace(nodes.size() - 2);
			nodesToResolve.emplace(nodes.size() - 1);
		}

		// Pop the top value of the queue.
		nodesToResolve.pop();
	}
}


void T_racer_BVH_Tree::getSplitCost(int nodeIndex, BVHSplitInfo& splitInfo)
{
	float parentSA = nodes[nodeIndex].getBounds()->getSurfaceArea();
	float invSA = 1 / parentSA;
	float bestCost = INFINITY;
	float currentCost = INFINITY;

	std::vector<BVHPrimative>  primatives;
	std::vector<int>&   primativeRef = nodes[nodeIndex].getTriangleIndexList();

	// Sort the boxes in order along an axis.
	BVHPrimative newPrim;
	newPrim.triangles = sceneObjects;

	for (int i = 0; i < primativeRef.size(); i++) 
	{
		newPrim.primativeID = primativeRef[i];
		newPrim.axis = splitInfo.axis;
		primatives.emplace_back(newPrim);
	}
	std::sort(primatives.begin(), primatives.end(), primativeSort);

	T_racer_Collider_AABB leftBox;
	T_racer_Collider_AABB rightBox;

	int leftCount = 0;
	int rightCount = 0;

	splitInfo.lPrims.reserve(primatives.size());
	splitInfo.rPrims.reserve(primatives.size());

	// Perform the testing.
	for (int j = 0; j < primatives.size(); j++) 
	{
		splitInfo.lPrims.clear();
		splitInfo.rPrims.clear();

		leftBox = T_racer_Collider_AABB();
		rightBox = T_racer_Collider_AABB();

		leftCount = (j);
		rightCount = primatives.size() - (j);

		for (int l = 0; l < j; l++) 
		{
			leftBox.enlargeBox((*sceneObjects)[primatives[l].primativeID].getCollider());
			splitInfo.lPrims.emplace_back(primatives[l].primativeID);
		}
		for (int r = j; r < primatives.size(); r++) 
		{
			rightBox.enlargeBox((*sceneObjects)[primatives[r].primativeID].getCollider());
			splitInfo.rPrims.emplace_back(primatives[r].primativeID);
		}

		currentCost = T_RACER_BVH_COST_TRAVERSAL_NODES
			+ (getGeometricProbibility(leftBox, invSA) * (T_RACER_BVH_COST_INTERSECTION_TRIANGLE * leftCount))
		    + (getGeometricProbibility(rightBox, invSA) * (T_RACER_BVH_COST_INTERSECTION_TRIANGLE * rightCount));

		if (currentCost < bestCost) 
		{
			splitInfo.splitCost = currentCost;
			splitInfo.lChildBox = leftBox;
			splitInfo.rChildBox = rightBox;
			bestCost = currentCost;
		}
	}
}

BVHSplitInfo T_racer_BVH_Tree::shouldPartition(int nodeIndex)
{
	float surfaceArea = nodes[nodeIndex].getBounds()->getSurfaceArea();
	BVHSplitInfo  bestCost;
	BVHSplitInfo  currentCost;
	bestCost.splitCost = INFINITY;  // This should hold true if no good splits are found.
	bestCost.axis = -1;

	if (nodes[nodeIndex].getTriangleIndexList().size() <= T_RACER_BVH_TRIANGLE_MAX_QUOTA) 
	{
		bestCost.split = false;
		return bestCost;
	}

	// for each axis we perform the SAH test.
	for (int i = 0; i < 3; i++) 
	{
		currentCost.axis = i;
		getSplitCost(nodeIndex, currentCost);

		if (currentCost.splitCost < bestCost.splitCost)
		{
			bestCost = currentCost;
		}
	}

	// Should we split.
	// If so generate the boxes used from splitting.
	// else just set to false.
	bestCost.split = (bestCost.splitCost != INFINITY);

	return bestCost;
}

float T_racer_BVH_Tree::getGeometricProbibility(T_racer_Collider_AABB& col, float invSurfaceArea)
{
	return col.getSurfaceArea() * invSurfaceArea;
}