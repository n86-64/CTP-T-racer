#include "Triangle.h"

#define ELIPSION 1e-8

Triangle::Triangle(T_racer_Vertex v1, T_racer_Vertex v2, T_racer_Vertex v3)
{
	verticies[0] = v1;
	verticies[1] = v2;
	verticies[2] = v3;
}

T_racer_TriangleIntersection Triangle::isIntersecting(T_racer_Math::Ray ray)
{
	T_racer_TriangleIntersection  intersect;

	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	// Calculate the determinant for the matrix
	T_racer_Math::Vector   pVec = T_racer_Math::cross(ray.getDirection(), v2v0);
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
	T_racer_Math::Vector tVec = ray.getPosition() - verticies[0].position;
	T_racer_Math::Vector qVec = T_racer_Math::cross(tVec, v1v0);

	intersect.t = T_racer_Math::dot(qVec, v2v0);

	if (intersect.t == INFINITY && intersect.t < ELIPSION)
	{
		intersect.intersection = false;
		return intersect;
	}

	intersect.u = T_racer_Math::dot(pVec, tVec) * determinant;
	if (intersect.u < 0.0f || intersect.u > 1.0f)
	{
		intersect.intersection = false;
		return intersect;
	}
	intersect.v = T_racer_Math::dot(qVec, ray.getDirection()) * determinant;
	if (intersect.v < 0.0f || intersect.v > 1.0f)
	{
		intersect.intersection = false;
		return intersect;
	}

	intersect.intersection = (intersect.v + intersect.u) < 1.0f;
	intersect.setW();

	return intersect;
}

bool Triangle::isIntersectingShadow(T_racer_Math::Ray ray, const float maxt)
{
	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	// Calculate the determinant for the matrix
	T_racer_Math::Vector   pVec = T_racer_Math::cross(ray.getDirection(), v2v0);
	float determinant = T_racer_Math::dot(pVec, v1v0);

	// Check to see if we should continue.
	// Here we can cull the triangle if nescessery. 
	if (determinant <= 1e-8)
	{
		return false;
	}

	// Inverse the determinant for scaling. 
	determinant = 1 / determinant;
	T_racer_Math::Vector tVec = ray.getPosition() - verticies[0].position;
	T_racer_Math::Vector qVec = T_racer_Math::cross(tVec, v1v0);

	float t;

	t = T_racer_Math::dot(qVec, v2v0);

	if (t > maxt || t < 1e-4)
	{
		return false;
	}

	float u = T_racer_Math::dot(pVec, tVec) * determinant;
	if (u < 0.0f || u > 1.0f)
	{
		return 0;
	}
	float v = T_racer_Math::dot(qVec, ray.getDirection()) * determinant;
	if (v < 0.0f || v > 1.0f)
	{
		return 0;
	}

	if ((v + u) < 1.0f)
	{
		return 1.0f;
	}

	return 0;
}

T_racer_Math::Vector Triangle::interpolatePoint(T_racer_TriangleIntersection iCoord)
{
	T_racer_Math::Vector  returnCoord;

	// TODO - Fetch colour from texture.
	returnCoord = (verticies[0].texCoord * iCoord.u) + (verticies[1].texCoord * iCoord.v) + (verticies[2].texCoord * iCoord.w);

	return returnCoord;
}

T_racer_Math::Vector Triangle::interpolateNormals(T_racer_TriangleIntersection iCoord)
{
	return T_racer_Math::Vector((verticies[0].normal * iCoord.u) + (verticies[1].normal * iCoord.v) + (verticies[2].normal * iCoord.w));
}
