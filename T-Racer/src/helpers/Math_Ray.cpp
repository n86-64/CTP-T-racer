#include <assert.h>
#include "Math_Ray.h"

namespace T_racer_Math 
{
	Ray::Ray() : Ray(Vector(0,0,0), Vector(1,1,1))
	{}

	Ray::Ray(Vector origin, Vector dir):
		position(origin),
		direction(dir)
	{
		inverseDirection = direction.inverse(1);
	}

	Vector Ray::getInverseDirection()
	{
		return inverseDirection;
	}

	void Ray::setDirection(Vector dir)
	{
		direction = dir; 
		inverseDirection = direction.inverse(1); 
		incomingRayDirection = -direction;
	//	normal = incomingRayDirection.normalise();
	}
}