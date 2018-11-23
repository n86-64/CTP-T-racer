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

class T_racer_Collider_AABB 
{
public:
	T_racer_Collider_AABB() = default;
	T_racer_Collider_AABB(T_racer_Math::Vector  vMin, T_racer_Math::Vector vMax);

	bool isIntersected(T_racer_Math::Ray  ray);
	bool isIntersected(T_racer_Collider_AABB box);

	void enlargeBox(T_racer_Math::Vector point);
	void enlargeBox(T_racer_Collider_AABB& collider);

	T_racer_Math::Vector getBoxMidpoint();
	T_racer_Math::Vector getBoxHalfLength();
	T_racer_Math::Vector getBoxLength() { return getBoxHalfLength() * 2; }

	T_racer_Math::Vector getMin() const { return min; };
	T_racer_Math::Vector getMax() const { return max; };

private:
	T_racer_Math::Vector   min = T_racer_Math::Vector(INFINITY, INFINITY, INFINITY);
	T_racer_Math::Vector	max = T_racer_Math::Vector(-INFINITY, -INFINITY, -INFINITY);
};
