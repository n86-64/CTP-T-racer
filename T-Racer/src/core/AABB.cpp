#include "AABB.h"

AABB::AABB(T_racer_Math::Vector3 vMin, T_racer_Math::Vector3 vMax)
	:min(vMin),
	max(vMax)
{}

bool AABB::isIntersected(T_racer_Math::Ray ray)
{
	T_racer_Math::Vector3  tmax;
	T_racer_Math::Vector3  tmin;

	T_racer_Math::Vector3 rayDir = ray.getInverseDirection();
	T_racer_Math::Vector3 rayPos = ray.getPosition();
	bool intersection = false;

	tmin = min;
	tmax = max;

	if (tmin.x() <= 0) { float temp = tmin.x(); tmin.x(tmax.x()); tmax.x(temp); }
	if (tmin.y() <= 0) { float temp = tmin.y(); tmin.y(tmax.y()); tmax.y(temp); }
	if (tmin.z() <= 0) { float temp = tmin.z(); tmin.z(tmax.z()); tmax.z(temp); }

	tmin = (tmin - rayPos) * rayDir;
	tmax = (tmax - rayPos) * rayDir;

	return (tmin.x() < tmax.x()) && (tmin.y() < tmax.y()) && (tmin.z() < tmax.z());
}

bool AABB::isIntersected(AABB box)
{
	if (max.x() > box.min.x() && min.x() < box.max.x()) 
	{
		if (max.y() > box.min.y() && min.y() < box.max.y())
		{
			if (max.z() > box.min.z() && min.z() < box.max.z())
			{
				return true;
			}
		}
	}

	return false;
}

void AABB::enlargeBox(T_racer_Math::Vector3 point)
{
	if (point.X > max.X || point.Y > max.Y || point.Z > max.Z)
	{
		// Change the box size.
		max = point;
	}

	if (point.X < min.X || point.Y < min.Y || point.Z < min.Z)
	{
		// Change the box size.
		min = point;
	}

	return;
}
