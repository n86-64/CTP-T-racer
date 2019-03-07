#include <cmath>

#include "helpers/Math_Error.h"
#include "helpers/Math_Sampler.h"

#include "Triangle.h"


Triangle::Triangle(T_racer_Vertex v1, T_racer_Vertex v2, T_racer_Vertex v3)
{
	verticies[0] = v1;
	verticies[1] = v2;
	verticies[2] = v3;

	normal = getNormal();
}

T_racer_TriangleIntersection Triangle::isIntersecting(T_racer_Math::Ray* ray)
{
	T_racer_TriangleIntersection  intersect;

	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	float rcp = 1.0f / T_racer_Math::dot(T_racer_Math::cross(v1v0, v2v0), ray->direction);
	T_racer_Math::Vector v2 = verticies[0].position - ray->position;

	intersect.t = T_racer_Math::dot(T_racer_Math::cross(v1v0, v2v0), v2) * rcp;

	if (intersect.t < T_RACER_EPSILON)
	{
		intersect.intersection = false;
		return intersect;
	}

	T_racer_Math::Vector v3 = T_racer_Math::cross(ray->direction, v2);

	intersect.u = T_racer_Math::dot(v3, v2v0) * -rcp;

	if (intersect.u < 0.0f || intersect.u > 1.0f)
	{
		intersect.intersection = false;
		return intersect;
	}

	intersect.v = T_racer_Math::dot(v3, v1v0) * rcp;

	if (intersect.v < 0.0f || (intersect.v + intersect.u) > 1.0f)
	{
		intersect.intersection = false;
		return intersect;
	}

	intersect.intersection = true;
	intersect.setW();

	return intersect;

	//// Calculate the determinant for the matrix
	//T_racer_Math::Vector   pVec = T_racer_Math::cross(ray->direction, v2v0);
	//float determinant = T_racer_Math::dot(pVec, v1v0);

	//// Check to see if we should continue.
	//// Here we can cull the triangle if nescessery. 
	//if (determinant <= T_RACER_EPSILON) 
	//{
	//	intersect.intersection = false;
	//	return intersect;
	//}

	//// Inverse the determinant for scaling. 
	//determinant = 1 / determinant;
	//T_racer_Math::Vector tVec = ray->position - verticies[0].position;
	//T_racer_Math::Vector qVec = T_racer_Math::cross(tVec, v1v0);

	//intersect.t = T_racer_Math::dot(qVec, v2v0) * determinant;

	//if (intersect.t == INFINITY || intersect.t < T_RACER_EPSILON)
	//{
	//	intersect.intersection = false;
	//	return intersect;
	//}

	//intersect.u = T_racer_Math::dot(pVec, tVec) * determinant;
	//if (intersect.u < 0.0f || intersect.u > 1.0f)
	//{
	//	intersect.intersection = false;
	//	return intersect;
	//}
	//intersect.v = T_racer_Math::dot(qVec, ray->direction) * determinant;
	//if (intersect.v < 0.0f || intersect.v > 1.0f)
	//{
	//	intersect.intersection = false;
	//	return intersect;
	//}

	//intersect.intersection = (intersect.v + intersect.u) <= 1.0f;
	//intersect.setW();

	//return intersect;
}

bool Triangle::isIntersectingShadow(T_racer_Math::Ray* ray, const float maxt)
{
	T_racer_TriangleIntersection  intersect;

	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	float rcp = 1.0f / T_racer_Math::dot(T_racer_Math::cross(v1v0, v2v0), ray->direction);
	T_racer_Math::Vector v2 = verticies[0].position - ray->position;

	intersect.t = T_racer_Math::dot(T_racer_Math::cross(v1v0, v2v0), v2) * rcp;

	if (intersect.t < T_RACER_EPSILON || intersect.t > maxt)
	{
		return 0;
	}

	T_racer_Math::Vector v3 = T_racer_Math::cross(ray->direction, v2);

	intersect.u = T_racer_Math::dot(v3, v2v0) * -rcp;

	if (intersect.u < 0.0f || intersect.u > 1.0f)
	{
		return 0;
	}

	intersect.v = T_racer_Math::dot(v3, v1v0) * rcp;

	if (intersect.v < 0.0f || (intersect.v + intersect.u) > 1.0f)
	{
		return 0;
	}

	return 1;

	//T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	//T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	//// Calculate the determinant for the matrix
	//T_racer_Math::Vector   pVec = T_racer_Math::cross(ray->direction, v2v0);
	//float determinant = T_racer_Math::dot(pVec, v1v0);

	//// Check to see if we should continue.
	//// Here we can cull the triangle if nescessery. 
	//if (determinant <= T_RACER_EPSILON)
	//{
	//	return false;
	//}

	//// Inverse the determinant for scaling. 
	//determinant = 1 / determinant;
	//T_racer_Math::Vector tVec = ray->position - verticies[0].position;
	//T_racer_Math::Vector qVec = T_racer_Math::cross(tVec, v1v0);

	//float t;

	//t = T_racer_Math::dot(qVec, v2v0) * determinant;

	//if (t > maxt || t < T_RACER_EPSILON)
	//{
	//	return false;
	//}

	//float u = T_racer_Math::dot(pVec, tVec) * determinant;
	//if (u < 0.0f || u > 1.0f)
	//{
	//	return 0;
	//}
	//float v = T_racer_Math::dot(qVec, ray->direction) * determinant;
	//if (v < 0.0f || v > 1.0f)
	//{
	//	return 0;
	//}

	//if ((v + u) < 1.0f)
	//{
	//	return 1.0f;
	//}

	//return 0;
}

T_racer_Math::Matrix3X3 Triangle::createShadingFrame(T_racer_Math::Vector v)
{
	float invLen = 0.0f;
	T_racer_Math::Vector v2;
	T_racer_Math::Vector v3;

	if (fabsf(v.X) > fabsf(v.Y)) 
	{
		invLen = 1.0f / sqrtf((v.X * v.X) + (v.Z * v.Z));
		v2 = T_racer_Math::Vector(-v.Z * invLen, 0.0f, v.X * invLen);
	}
	else 
	{
		invLen = 1.0f / sqrtf((v.Y * v.Y) + (v.Z * v.Z));
		v2 = T_racer_Math::Vector(0.0f, v.Z * invLen, -v.Y * invLen);
	}

	v3 = T_racer_Math::cross(v, v2);

	return T_racer_Math::Matrix3X3 // Returns an outhogonal matrix.
	(
		v2.X, v2.Y, v2.Z,
		v3.X, v3.Y, v3.Z,
		v.X, v.Y, v.Z
	);
}

float Triangle::getSurfaceArea()
{
	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	return T_racer_Math::cross(v1v0, v2v0).Magnitude() * 0.5f;
}

T_racer_Math::Vector Triangle::samplePoint()
{
	T_racer_Math::Sampler sampler;
	T_racer_Math::Vector  sampleVal;

	sampleVal = sampler.Random2();

	float sul = sqrtf(sampleVal.X);
	float u = 0.0f, v = 0.0f, w = 0.0f;

	u = 1.0f - sul;
	v = sampleVal.Y * sul;
	w = 1 - u - v;

	return (verticies[0].position * u) + (verticies[1].position * v) + (verticies[2].position * w);
}

T_racer_Math::Vector Triangle::getNormal()
{
	T_racer_Math::Vector  v1v0 = verticies[1].position - verticies[0].position;
	T_racer_Math::Vector  v2v0 = verticies[2].position - verticies[0].position;

	return T_racer_Math::cross(v1v0, v2v0).normalise();
}

T_racer_Math::Vector Triangle::getMinVector()
{
	float axisValues[3];
	for (int i = 0; i < 3; i++) 
	{
		axisValues[i] = fminf(verticies[0].position.values[i], verticies[1].position.values[i]);
		axisValues[i] = fminf(axisValues[i], verticies[2].position.values[i]);
	}

	return T_racer_Math::Vector(axisValues[0], axisValues[1], axisValues[2]);
}

T_racer_Math::Vector Triangle::getMaxVector()
{
	float axisValues[3];
	for (int i = 0; i < 3; i++)
	{
		axisValues[i] = fmaxf(verticies[0].position.values[i], verticies[1].position.values[i]);
		axisValues[i] = fmaxf(axisValues[i], verticies[2].position.values[i]);
	}

	return T_racer_Math::Vector(axisValues[0], axisValues[1], axisValues[2]);
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

void Triangle::generateBoundingBox()
{
	collider = T_racer_Collider_AABB
	(
		getMinVector(),
		getMaxVector()
	);
}
