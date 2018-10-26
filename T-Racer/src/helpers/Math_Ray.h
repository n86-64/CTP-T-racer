/** @file Math_Ray.h
*  @brief A ray definition.
*
*  Defines a ray originating from a point in 3D space. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <limits>
#include "Math_Vector.h"

namespace T_racer_Math 
{
	class Ray 
	{
	public:
		Ray();
		Ray(Vector3 origin, Vector3 dir);

		Vector3 getPosition() const { return position; }
		Vector3 getDirection() const { return direction; }
		Vector3 getInverseDirection();

		void	setPosition(Vector3 pos) { position = pos; }
		void	setDirection(Vector3 dir) { direction = dir; }

	private:
		Vector3  position;
		Vector3  direction;
		float	 magnitude = FLT_MAX; // Maybe need, not sure.
	};
}