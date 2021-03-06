/** @file Triangle.h
*  @brief Triangle Object.
*
*  Defines a triangle primitive along with triangle operators.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#include <assert.h>

#pragma once

#include "core/Vertex.h"
#include "core/Intersection.h"
#include "helpers/Math_Ray.h"
#include "helpers/Math_Colour.h"
#include "helpers/Math_Matrix.h"
#include "AABB.h"

constexpr int VERTEX_COUNT = 3;

class Triangle 
{
public:
	Triangle() = default;
	Triangle(T_racer_Vertex* v1, T_racer_Vertex* v2, T_racer_Vertex* v3);
	Triangle(T_racer_Vertex v1, T_racer_Vertex v2, T_racer_Vertex v3);

	T_racer_TriangleIntersection   isIntersecting(T_racer_Math::Ray*  ray);
	T_racer_Math::Vector		   interpolatePoint(T_racer_TriangleIntersection iCoord);
	T_racer_Math::Vector           interpolateNormals(T_racer_TriangleIntersection iCoord);
	void						   generateBoundingBox();
	bool						   isIntersectingShadow(T_racer_Math::Ray* ray, const float maxt);
	
	T_racer_Math::Matrix3X3		   createShadingFrame(T_racer_Math::Vector v);

	float						   getSurfaceArea();
	T_racer_Math::Vector		   samplePoint();

	T_racer_Math::Vector		   getNormal();
	T_racer_Math::Vector		   getSmoothNormal(T_racer_TriangleIntersection& intersect);

	T_racer_Collider_AABB&		   getCollider() { return collider; };

	int							   getMaterialIndex() const { return materialID; }
	void						   setMaterialIndex(int id) { materialID = id; }

	T_racer_Math::Vector		   normal;

	T_racer_Vertex   verticies[VERTEX_COUNT] = { 0 };

private:
	T_racer_Math::Vector getMinVector();
	T_racer_Math::Vector getMaxVector();

private:
	T_racer_Collider_AABB					collider;
	unsigned int					  materialID = 0;
};