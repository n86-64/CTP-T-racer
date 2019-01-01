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
		Vector getincomingRayDirection() { return incomingRayDirection; }

		void	setPosition(Vector pos) { position = pos; }
		void	setDirection(Vector dir);

		float	getMagnitude() { return magnitude; }
		void    setMagnitude(float newLength) { magnitude = newLength; }

		void	setUV(float u, float v) { uv.values[0] = u; uv.values[1] = v; };
		Vector  getUV() { return uv; }
		
		void	setHitPoint(Vector point) { hitPoint = point; };
		void    setOrthonormalBasis(Vector orthonormal) { orthnormalBasis = orthonormal; }

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