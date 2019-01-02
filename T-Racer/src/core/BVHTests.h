/** @file BVHNode.h
*  @brief A data-structure for use in the BVH.
*
*  Simply contains a list of triangle indexes to test.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>
#include "helpers/Math_Ray.h"

struct T_racer_BVH_CollisionQueue_t
{
	// The triangles we need to test from the scene.
	std::vector<int>  triangleIndexes;
	T_racer_Math::Ray ray;
};