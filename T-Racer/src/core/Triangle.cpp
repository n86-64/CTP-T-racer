#include "Triangle.h"

Triangle::Triangle(T_racer_Vertex v1, T_racer_Vertex v2, T_racer_Vertex v3)
{
	verticies[0] = v1;
	verticies[1] = v2;
	verticies[2] = v3;
}

T_racer_TriangleIntersection Triangle::isIntersecting(T_racer_Math::Ray ray)
{
	T_racer_TriangleIntersection  intersect;

	T_racer_Math::Vector3  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector3  v2v0 = verticies[2].position - verticies[0].position;

	// Calculate the determinant for the matrix
	T_racer_Math::Vector3   pVec = T_racer_Math::cross(ray.getDirection(), v2v0);
	float determinant = T_racer_Math::dot(pVec, v1v0);

	// Check to see if we should continue.
	// Here we can cull the triangle if nescessery. 
	if (determinant <= 1e-8) 
	{
		intersect.intersection = false;
		return intersect;
	}

	// Inverse the determinant for scaling. 
	determinant = 1 / determinant;
	T_racer_Math::Vector3 tVec = ray.getPosition() - verticies[0].position;
	T_racer_Math::Vector3 qVec = T_racer_Math::cross(tVec, v1v0);

	intersect.u = T_racer_Math::dot(pVec, tVec) * determinant;
	intersect.v = T_racer_Math::dot(qVec, ray.getDirection()) * determinant;

	intersect.intersection = (intersect.u > 0.0f || intersect.u < 1.0f) && (intersect.v > 0.0f || (intersect.v + intersect.u) < 1.0f);
	intersect.setW();

	if (intersect.intersection) 
	{
		intersect.t = T_racer_Math::dot(qVec, v2v0);
	}

	return intersect;
}
