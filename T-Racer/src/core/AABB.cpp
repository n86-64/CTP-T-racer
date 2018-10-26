#include "AABB.h"

AABB::AABB(T_racer_Math::Vector3 vMin, T_racer_Math::Vector3 vMax)
	:min(vMin),
	max(vMax)
{}

bool AABB::isIntersected(T_racer_Math::Ray ray)
{
	T_racer_Math::Vector3  tmax;
	T_racer_Math::Vector3  tmin;

	T_racer_Math::Vector3 rayDir = ray.getDirection();
	bool intersection = false;

	

	return intersection;
}
