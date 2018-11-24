#include <stdio.h>
#include "helpers/Math_neumeric.h"

#include "AABB.h"

T_racer_Collider_AABB::T_racer_Collider_AABB(T_racer_Math::Vector vMin, T_racer_Math::Vector vMax)
	:min(vMin),
	max(vMax)
{}

bool T_racer_Collider_AABB::isIntersected(T_racer_Math::Ray ray)
{	
	T_racer_Math::Vector inv = ray.getInverseDirection();

	T_racer_Math::Vector point0 = (min - ray.getPosition()) * inv;
	T_racer_Math::Vector point1 = (max - ray.getPosition()) * inv;

	T_racer_Math::Vector tMin = T_racer_Math::min(point0, point1); 
	T_racer_Math::Vector tMax = T_racer_Math::max(point0, point1);

	return (tMin.maxComp() <= tMax.minComp()); 
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

void T_racer_Collider_AABB::enlargeBox(T_racer_Collider_AABB& collider)
{
	min.X = fminf(min.X, collider.getMin().X);
	min.Y = fminf(min.Y, collider.getMin().Y);
	min.Z = fminf(min.Z, collider.getMin().Z);
	
	max.X = fmaxf(max.X, collider.getMax().X);
	max.Y = fmaxf(max.Y, collider.getMax().Y);
	max.Z = fmaxf(max.Z, collider.getMax().Z);
}

T_racer_Math::Vector T_racer_Collider_AABB::getBoxMidpoint()
{
	return min + getBoxHalfLength();
}

T_racer_Math::Vector T_racer_Collider_AABB::getBoxHalfLength()
{
	return ((max - min) / 2);
}

float T_racer_Collider_AABB::getSurfaceArea()
{
	float surfaceArea = 0.0f;
	T_racer_Math::Vector boxDiameter = getBoxLength();
	surfaceArea = 2.0f * ((boxDiameter.X * boxDiameter.Y) + (boxDiameter.Y * boxDiameter.Z) + (boxDiameter.X * boxDiameter.Z));

	return surfaceArea;
}
