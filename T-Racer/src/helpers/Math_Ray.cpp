#include <assert.h>
#include "Math_Ray.h"

namespace T_racer_Math 
{
	Ray::Ray() : Ray(Vector3(0,0,0), Vector3(1,1,1))
	{}

	Ray::Ray(Vector3 origin, Vector3 dir):
		position(origin),
		direction(dir)
	{}

	Vector3 T_racer_Math::Ray::getInverseDirection()
	{
		assert((direction.x() != 0.0f) && (direction.y() != 0.0f) && (direction.z() != 0.0f));
		return Vector3(1.0f / direction.x(), 1.0f / direction.y(), 1.0f / direction.z());
	}
}