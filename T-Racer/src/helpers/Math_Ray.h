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
	// Defines a ray located within world space.
	class Ray 
	{
	public:
		Ray();
		Ray(Vector origin, Vector dir);

		Vector getPosition() const { return position; }
		Vector getDirection() const { return direction; }
		Vector getInverseDirection();

		void	setPosition(Vector pos) { position = pos; }
		void	setDirection(Vector dir) { direction = dir; inverseDirection = direction.inverse(1); incomingRayDirection = -direction; }

		float	getMagnitude() { return magnitude; }
		void    setMagnitude(float newLength) { magnitude = newLength; }

	private:
		Vector  position;
		Vector  direction;
		Vector  inverseDirection; // TODO - Apply inverse direction to the ray.
		Vector  incomingRayDirection;
		float	magnitude = INFINITY; // Maybe need, not sure.

		// Additional ray properties
		Vector uv;
		Vector normal;
		Vector orthnormalBasis;
		Vector hitPoint;

		int	   BRDFMaterialID = 0;
	};
}