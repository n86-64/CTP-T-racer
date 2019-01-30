#include <queue>
#include <deque>

#include "helpers/FileReader.h"

#include "BVHTree.h"

// Intersection cost constants.
// Used for Surface area heuristic.
// Constants derived from PBRT 3rd edition (p.g. 207)
constexpr int T_RACER_BVH_COST_TRAVERSAL_NODES = 1;
constexpr int T_RACER_BVH_COST_INTERSECTION_TRIANGLE = 80;
constexpr int T_RACER_BVH_TRIANGLE_MAX_QUOTA = 2;
constexpr float T_RACER_BVH_PARTITION = -1.0f;
constexpr int T_RACER_BVH_QUEUE_MAX_DEPTH = 50;

// Predicate for sorting triangles along an axis.
bool triangleSort(BVHEdge a, BVHEdge b) 
{
	return (a.t < b.t);
}

bool primativeSort(BVHPrimative& a, BVHPrimative& b) 
{
	return (*a.triangles)[a.primativeID].getCollider().getBoxMidpoint().values[a.axis] < (*b.triangles)[b.primativeID].getCollider().getBoxMidpoint().values[b.axis];
}

T_racer_BVH_Tree::T_racer_BVH_Tree()
{
	nodes.reserve(T_RACER_BVH_NODE_PREALLOC);
}

T_racer_BVH_Tree::~T_racer_BVH_Tree()
{

}

void T_racer_BVH_Tree::generateSceneBVH(std::string name, std::vector<Triangle>* scenePrimatives)
{
	sceneObjects = scenePrimatives;

	if (!loadBVHFromFile(name)) 
	{
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
		saveBVHToFile(name);
	}
}

T_racer_TriangleIntersection T_racer_BVH_Tree::checkForIntersections(T_racer_Math::Ray* ray)
{
	// Perform the intersection test for the ray.

	int nodesToCheck[T_RACER_BVH_QUEUE_MAX_DEPTH];
	std::fill_n(nodesToCheck, T_RACER_BVH_QUEUE_MAX_DEPTH, -1);
	int nodeToCheckIndex = 0;
	nodesToCheck[nodeToCheckIndex] = 0;

	T_racer_BVH_Node* currentNode = nullptr;

	T_racer_TriangleIntersection  triIntersection;

	while (nodeToCheckIndex != -1)
	{
		currentNode = &nodes[nodesToCheck[nodeToCheckIndex]];

		if (currentNode->getBounds()->isIntersected(*ray))
		{
			if (currentNode->getLeftNode() != T_RACER_NODE_NULL &&
				currentNode->getRightNode() != T_RACER_NODE_NULL)
			{
				nodesToCheck[nodeToCheckIndex] = currentNode->getLeftNode();
				nodesToCheck[nodeToCheckIndex + 1] = currentNode->getRightNode();

				nodeToCheckIndex = nodeToCheckIndex + 1;
			}

			else
			{
				// its a leaf we dont need to check this anymore.

				for (int i = 0; i < currentNode->getTriangleIndexList().size(); i++)
				{
					T_racer_TriangleIntersection  triIntersectiont;
					triIntersectiont = (*sceneObjects)[currentNode->getTriangleIndexList()[i]].isIntersecting(*ray);
					if (triIntersectiont.intersection && triIntersectiont.t < triIntersection.t)
					{
						triIntersection = triIntersectiont;
						triIntersection.triangleID = currentNode->getTriangleIndexList()[i];
					}
				}
				nodesToCheck[nodeToCheckIndex] = -1;
				nodeToCheckIndex--;
			}
		}
		else
		{
			nodesToCheck[nodeToCheckIndex] = -1;
			nodeToCheckIndex--;
		}
	}
	return triIntersection;
}

bool T_racer_BVH_Tree::visible(T_racer_Math::Ray* ray, const float t)
{

	int nodesToCheck[T_RACER_BVH_QUEUE_MAX_DEPTH];
	std::fill_n(nodesToCheck, T_RACER_BVH_QUEUE_MAX_DEPTH, -1);
	int nodeToCheckIndex = 0;
	nodesToCheck[nodeToCheckIndex] = 0;

	T_racer_BVH_Node* currentNode = nullptr;

	while (nodeToCheckIndex != -1)
	{
		if (nodesToCheck[nodeToCheckIndex] != -1)
		{
			currentNode = &nodes[nodesToCheck[nodeToCheckIndex]];

			if (currentNode->getBounds()->isIntersected(*ray))
			{
				if (currentNode->getLeftNode() != T_RACER_NODE_NULL &&
					currentNode->getRightNode() != T_RACER_NODE_NULL)
				{
					nodesToCheck[nodeToCheckIndex] = currentNode->getLeftNode();
					nodesToCheck[nodeToCheckIndex + 1] = currentNode->getRightNode();

					nodeToCheckIndex = nodeToCheckIndex + 1;
				}

				else
				{
					// its a leaf we dont need to check this anymore.

					for (int i = 0; i < currentNode->getTriangleIndexList().size(); i++)
					{
						T_racer_TriangleIntersection  triIntersectiont;
						triIntersectiont = (*sceneObjects)[currentNode->getTriangleIndexList()[i]].isIntersecting(*ray);
						if (triIntersectiont.intersection && triIntersectiont.t < t && triIntersectiont.t > 0)
						{
							return false;
						}
					}
					nodesToCheck[nodeToCheckIndex] = -1;
					nodeToCheckIndex--;
				}
			}
			else
			{
				nodeToCheckIndex--;
			}
		}
		else
		{
			nodeToCheckIndex--;
		}
	}
	return true;
}

bool T_racer_BVH_Tree::loadBVHFromFile(std::string& name)
{
	std::string  value;
	std::string path = "resources/BVH/" + name + ".trbh";
	T_racer_Buffer  buffer(path);

	if (!buffer.readFile()) 
	{
		return false;
	}

	// Here we load the BVH.
	T_racer_Math::Vector  minVec;
	T_racer_Math::Vector  maxVec;

	size_t currentSize = sizeof(int);

	int nodeCount;
	int leftNode;
	int rightNode;
	int childCount;
	int primitiveCount;
	int child;

	// Retrieve the nodecount.

	buffer.extractData(&nodeCount, 0, currentSize);
	nodes.resize(nodeCount); // preallocate the tree.

	for (int i = 0; i < nodeCount; i++) 
	{
		buffer.extractData(&minVec.X, currentSize, sizeof(float));
		currentSize += sizeof(float);
		buffer.extractData(&minVec.Y, currentSize, sizeof(float));
		currentSize += sizeof(float);
		buffer.extractData(&minVec.Z, currentSize, sizeof(float));
		currentSize += sizeof(float);

		buffer.extractData(&maxVec.X, currentSize, sizeof(float));
		currentSize += sizeof(float);
		buffer.extractData(&maxVec.Y, currentSize, sizeof(float));
		currentSize += sizeof(float);
		buffer.extractData(&maxVec.Z, currentSize, sizeof(float));
		currentSize += sizeof(float);
		nodes[i].createBox(minVec, maxVec);

		buffer.extractData(&leftNode, currentSize, sizeof(int));
		currentSize += sizeof(int);
		buffer.extractData(&rightNode, currentSize, sizeof(int));
		currentSize += sizeof(int);
		nodes[i].assignNodes(leftNode, rightNode);

		// Get children.
		buffer.extractData(&childCount, currentSize, sizeof(int));
		currentSize += sizeof(int);

		for (int j = 0; j < childCount; j++) 
		{
			buffer.extractData(&child, currentSize, sizeof(int));
			currentSize += sizeof(int);
			nodes[i].addPrimativeIndicies(child);
		}
	}

	loadedBVH = true;
	return true;
}

void T_racer_BVH_Tree::saveBVHToFile(std::string& name)
{
	std::string bufferStr;
	std::string path = name + ".trbh";
	T_racer_Buffer  buffer(path);

	T_racer_Math::Vector  minVec;
	T_racer_Math::Vector  maxVec;

	// The number of nodes in the array.
	int nodeCount = nodes.size();
	int leftNode;
	int rightNode;
	int childCount;
	int child;
	bufferStr.append((const char*)&nodeCount, sizeof(int));

	for (int i = 0; i < nodeCount; i++) 
	{
		// Write the contents of each node.
		minVec = nodes[i].getBounds()->getMin();
		maxVec = nodes[i].getBounds()->getMax();

		bufferStr.append((const char*)&minVec.X, sizeof(float));
		bufferStr.append((const char*)&minVec.Y, sizeof(float));
		bufferStr.append((const char*)&minVec.Z, sizeof(float));
		bufferStr.append((const char*)&maxVec.X, sizeof(float));
		bufferStr.append((const char*)&maxVec.Y, sizeof(float));
		bufferStr.append((const char*)&maxVec.Z, sizeof(float));

		// Write the children to the file.
		leftNode = nodes[i].getLeftNode();
		rightNode = nodes[i].getRightNode();

		bufferStr.append((const char*)&leftNode, sizeof(int));
		bufferStr.append((const char*)&rightNode, sizeof(int));

		// if children append these onto the list.
		childCount = nodes[i].getNumberOfTriangles();
		bufferStr.append((const char*)&childCount, sizeof(int));

		for (int j = 0; j < childCount; j++) 
		{
			child = nodes[i].getTriangle(j);
			bufferStr.append((const char*)&child, sizeof(int));
		}
	}

	buffer.assignBufferData((uint8_t*)bufferStr.data(), bufferStr.size());
	buffer.writeFile();
}

void T_racer_BVH_Tree::createBVHNodes()
{
	// Implement tree construction here.
	T_racer_BVH_Node* childL = nullptr;
	T_racer_BVH_Node* childR = nullptr;

	// int currentNode = T_RACER_NODE_NULL;

	int nodesToResolve[T_RACER_BVH_QUEUE_MAX_DEPTH];
	std::fill_n(nodesToResolve, T_RACER_BVH_QUEUE_MAX_DEPTH, -1);
	int nodeToCheckIndex = 0;
	nodesToResolve[nodeToCheckIndex] = 0;

	//std::queue<int> nodesToResolve; // The indicies of the nodes we need to resolve.
	//nodesToResolve.emplace(0);
	BVHSplitInfo newSplit;

	while (nodesToResolve[nodeToCheckIndex] != -1) 
	{
		// Here we generate the child nodes and add them to the queue.
		newSplit = shouldPartition(nodesToResolve[nodeToCheckIndex]);

		if (newSplit.split) 
		{
			// Generate the next child nodes.
			nodes.emplace_back(T_racer_BVH_Node());
			nodes.emplace_back(T_racer_BVH_Node());

			childL = &nodes[nodes.size() - 2];
			childR = &nodes[nodes.size() - 1];

			// Set the boxes and primatives for each.
			nodes[nodesToResolve[nodeToCheckIndex]].assignNodes((int)nodes.size() - 2, (int)nodes.size() - 1);

			// Assign these there chosen bounding boxes.
			childL->assignBox(newSplit.lChildBox);
			childR->assignBox(newSplit.rChildBox);

			assert(newSplit.lChildBox.isValid());
			assert(newSplit.rChildBox.isValid());

			childL->setPrimativeIndicies(newSplit.lPrims);
			childR->setPrimativeIndicies(newSplit.rPrims);

			nodesToResolve[nodeToCheckIndex + 1] = nodes.size() - 2;
			nodesToResolve[nodeToCheckIndex + 2] = nodes.size() - 1;
		}

		// Pop the top value of the queue.
		nodeToCheckIndex++;
	}
}


void T_racer_BVH_Tree::getSplitCost(int nodeIndex, BVHSplitInfo& splitInfo)
{
	float parentSA = nodes[nodeIndex].getBounds()->getSurfaceArea();
	float invSA = 1 / parentSA;
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

	splitInfo.lPrims.clear();
	splitInfo.rPrims.clear();

	splitInfo.lPrims.reserve(primatives.size());
	splitInfo.rPrims.reserve(primatives.size());

	float bestCost = splitInfo.splitCost;

	float leftCost = 0.0f;
	float rightCost = 0.0f;

	// Perform the testing.
	for (int j = 0; j < primatives.size(); j++) 
	{
		leftBox = T_racer_Collider_AABB();
		rightBox = T_racer_Collider_AABB();

		leftCount = (j);
		rightCount = primatives.size() - (j);

		for (int left = 0; left < leftCount; left++) 
		{
			leftBox.enlargeBox((*sceneObjects)[primatives[left].primativeID].getCollider());
		}
		for (int right = leftCount; right < primatives.size(); right++) 
		{
			rightBox.enlargeBox((*sceneObjects)[primatives[right].primativeID].getCollider());
		}

		//leftBox.enlargeBox((*sceneObjects)[primatives[0].primativeID].getCollider());
		//leftBox.enlargeBox((*sceneObjects)[primatives[leftCount].primativeID].getCollider());
		//rightBox.enlargeBox((*sceneObjects)[primatives[leftCount].primativeID].getCollider());
		//rightBox.enlargeBox((*sceneObjects)[primatives[primatives.size() - 1].primativeID].getCollider());

		leftCost = (getGeometricProbibility(leftBox, parentSA) * (T_RACER_BVH_COST_INTERSECTION_TRIANGLE * leftCount));
		rightCost = getGeometricProbibility(rightBox, parentSA) * T_RACER_BVH_COST_INTERSECTION_TRIANGLE * rightCount;

		currentCost = T_RACER_BVH_COST_TRAVERSAL_NODES + leftCost + rightCost;

		if (currentCost < bestCost) 
		{
			splitInfo.splitCost = currentCost;
			splitInfo.lChildBox = leftBox;
			splitInfo.rChildBox = rightBox;

			// TODO - Compress to one variable.
			splitInfo.leftCount = leftCount;
			splitInfo.rightCount = rightCount;
			
			bestCost = currentCost;
		}
	}

	if (splitInfo.leftCount != -1 && splitInfo.rightCount != -1) 
	{
		for (int l = 0; l < splitInfo.leftCount; l++)
		{
			splitInfo.lPrims.emplace_back(primatives[l].primativeID);
		}
		for (int r = splitInfo.leftCount; r < primatives.size(); r++)
		{
			splitInfo.rPrims.emplace_back(primatives[r].primativeID);
		}
		splitInfo.split = true;
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
		currentCost.splitCost = nodes[nodeIndex].getTriangleIndexList().size() * T_RACER_BVH_COST_INTERSECTION_TRIANGLE;
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
//	bestCost.split = (bestCost.splitCost != INFINITY);

	return bestCost;
}

float T_racer_BVH_Tree::getGeometricProbibility(T_racer_Collider_AABB& col, float invSurfaceArea)
{
	//return col.getSurfaceArea() * invSurfaceArea;
	return col.getSurfaceArea() / invSurfaceArea;
}