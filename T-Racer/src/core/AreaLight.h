/** @file Area Light.h
*  @brief An Flat area light source.
*
*  Defines a light source comprised of sets of triangles emitting a light value of
*  x intensity. Utalises several sampling processes.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include <vector>

#include "Triangle.h"
#include "BaseLight.h"

class T_racer_Light_Area : public T_racer_Light_Base 
{
public: 
	T_racer_Light_Area();

	// Inherited via T_racer_Light_Base
	virtual void init(jsoncons::key_value<std::string, jsoncons::json> & initValues) override;

	virtual T_racer_Math::Colour Evaluate(T_racer_Path_Vertex & pathVertex) override;
	virtual T_racer_SampledDirection Sample(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex & lightSourceVertex) override;
	virtual float probabilityDensity(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay) override;
	virtual float surfaceCosine(T_racer_Path_Vertex & vertex) override;

	// Add triangles to the light.
	void  addTriangle(T_racer_Vertex a, T_racer_Vertex b, T_racer_Vertex c) { triangles.emplace_back(Triangle(a,b,c)); }

	virtual T_racer_TriangleIntersection doesIntersect(T_racer_Math::Ray* ray) override;

private:
	float pdfPoint = 0.0f;
	float pdfDirection = 0.0f;

	std::vector<Triangle>   triangles;
};