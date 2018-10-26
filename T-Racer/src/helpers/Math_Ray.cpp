#include <assert.h>
#include "Math_Ray.h"

namespace T_racer_Math 
{
	Ray::Ray() : Ray(Vector3(0,0,0), Vector3(1,1,1))
	{}

	Ray::Ray(Vector3 origin, Vector3 dir):
		position(origin),
		direction(dir)
	{
		inverseDirection = direction.inverse(1);
	}

	Vector3 Ray::getInverseDirection()
	{
		return inverseDirection;
	}
}