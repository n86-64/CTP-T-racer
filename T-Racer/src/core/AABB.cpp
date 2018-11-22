#include "AABB.h"

T_racer_Collider_AABB::T_racer_Collider_AABB(T_racer_Math::Vector vMin, T_racer_Math::Vector vMax)
	:min(vMin),
	max(vMax)
{}

bool T_racer_Collider_AABB::isIntersected(T_racer_Math::Ray ray)
{
	T_racer_Math::Vector  tmax;
	T_racer_Math::Vector  tmin;

	T_racer_Math::Vector rayDir = ray.getInverseDirection();
	T_racer_Math::Vector rayPos = ray.getPosition();
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

bool T_racer_Collider_AABB::isIntersected(T_racer_Collider_AABB box)
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

void T_racer_Collider_AABB::enlargeBox(T_racer_Math::Vector point)
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
