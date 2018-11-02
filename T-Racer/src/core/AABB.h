/** @file AABB.h
*  @brief Axis Aligned Bounding Box
*
*  Defines an AABB comprised of a min and max point.Allows
*  for enlargement and subdivision. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include <limits>
#include "helpers/Math_Vector.h"
#include "helpers/Math_Ray.h"

class AABB 
{
public:
	AABB() = default;
	AABB(T_racer_Math::Vector3  vMin, T_racer_Math::Vector3 vMax);

	bool isIntersected(T_racer_Math::Ray  ray);
	bool isIntersected(AABB box);

	void enlargeBox(T_racer_Math::Vector3 point);

private:
	T_racer_Math::Vector3   min = T_racer_Math::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	T_racer_Math::Vector3	max = T_racer_Math::Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
};
