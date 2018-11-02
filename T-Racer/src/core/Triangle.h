/** @file Triangle.h
*  @brief Triangle Object.
*
*  Defines a triangle primitive along with triangle operators.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "core/Vertex.h"
#include "core/Intersection.h"
#include "helpers/Math_Ray.h"
#include "helpers/Math_Colour.h"


constexpr int VERTEX_COUNT = 3;

class Triangle 
{
public:
	Triangle() = default;
	Triangle(T_racer_Vertex v1, T_racer_Vertex v2, T_racer_Vertex v3);

	T_racer_TriangleIntersection   isIntersecting(T_racer_Math::Ray  ray);
	T_racer_Math::Vector3		   interpolatePoint(T_racer_TriangleIntersection iCoord);
	T_racer_Math::Vector3          interpolateNormals(T_racer_TriangleIntersection iCoord);
	bool						   isIntersectingShadow(T_racer_Math::Ray ray, const float maxt);

private:
	T_racer_Vertex   verticies[VERTEX_COUNT] = { 0 };
	unsigned int					  materialID = 0;
};