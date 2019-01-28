/** @file BVHTree.h
*  @brief A basic container for a BVH tree.
*
*  A simple system that generates a BVH tree.
*  Used for optimising Ray Triangle Intersection.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "BVHNode.h"
#include "BVHTests.h"
#include "core/Triangle.h"


constexpr int T_RACER_BVH_NODE_PREALLOC = 100;


struct BVHEdge
{
	float t;
	int primativeRef = 0;
	int axis;
	bool startNode = true;
};

struct BVHPrimative 
{
	std::vector<Triangle>*  triangles;
	int primativeID = -1;
	int axis = -1;
};

struct BVHSplitInfo 
{
	bool split = false;
	T_racer_Collider_AABB  lChildBox;
	T_racer_Collider_AABB  rChildBox;
	std::vector<BVHPrimative>  prim;
	int						   splitPoint;
	std::vector<int> lPrims;
	std::vector<int> rPrims;
	float splitCost = 0.0f;
	int axis = -1;

	// NULL values.
	int leftCount = -1;
	int rightCount = -1;
};

class T_racer_BVH_Tree 
{
public:
	T_racer_BVH_Tree();
	~T_racer_BVH_Tree();

	void generateSceneBVH(std::string name, std::vector<Triangle>* scenePrimatives);
	T_racer_TriangleIntersection checkForIntersections(T_racer_Math::Ray* ray);
	bool visible(T_racer_Math::Ray* ray, const float t);

	int	  getIntersectedTriangle() const { return closestTriangle; }

private:
	bool loadBVHFromFile(std::string& name);
	void saveBVHToFile(std::string& name); 

	void createBVHNodes();

	// Splitting routienes.
	void getSplitCost(int nodeIndex, 
		BVHSplitInfo& splitInfo); // Implements Surface area Heuristic.

	BVHSplitInfo shouldPartition(int nodeIndex);

	float getGeometricProbibility(T_racer_Collider_AABB& col, float surfaceArea);

private:
	bool					  loadedBVH = false;
	int						  closestTriangle = -1;
	float					  closeT = INFINITY;

	std::vector<Triangle>*    sceneObjects;  // All objects in a scene.

	std::vector<T_racer_BVH_Node>   nodes = std::vector<T_racer_BVH_Node>(1);

	float surfaceArea = 0.0f;

	int maxDepth = 0; // Based on research in pbrt. (p.g 204 Real time rendering third edition.) 
};