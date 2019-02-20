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

class T_Racer_Light_Area : public T_racer_Light_Base 
{
public: 

	virtual T_racer_Math::Colour Evaluate(T_racer_Path_Vertex & pathVertex) override;
	virtual T_racer_SampledDirection Sample(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex & lightSourceVertex) override;
	virtual float probabilityDensity(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay) override;
	virtual float surfaceCosine(T_racer_Path_Vertex & vertex) override;

private:
	float pdfPoint = 0.0f;
	float pdfDirection = 0.0f;

	std::vector<Triangle>   triangles;
};