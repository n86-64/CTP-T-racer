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
	AABB(T_racer_Math::Vector  vMin, T_racer_Math::Vector vMax);

	bool isIntersected(T_racer_Math::Ray  ray);
	bool isIntersected(AABB box);

	void enlargeBox(T_racer_Math::Vector point);

private:
	T_racer_Math::Vector   min = T_racer_Math::Vector(FLT_MAX, FLT_MAX, FLT_MAX);
	T_racer_Math::Vector	max = T_racer_Math::Vector(-FLT_MAX, -FLT_MAX, -FLT_MAX);
};
