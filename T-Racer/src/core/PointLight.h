/** @file PointLight.h
*  @brief A point light.
*
*  A basic light where all light is emitted equally from a point in space.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "BaseLight.h"

class T_racer_Light_Point : public T_racer_Light_Base 
{
public:
	T_racer_Light_Point() = default;

	// Inherited via T_racer_Light_Base
	virtual void init(jsoncons::key_value<std::string, jsoncons::json> & initValues) override;

	// Inherited via T_racer_Light_Base
	virtual T_racer_Math::Colour Evaluate(T_racer_Path_Vertex& pathVertex) override;
	virtual T_racer_SampledDirection  Sample(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex& lightSourcePath) override;
	virtual float probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray & inputRay) override;
	virtual float surfaceCosine(T_racer_Path_Vertex& vertex) override;

	virtual T_racer_TriangleIntersection doesIntersect(T_racer_Math::Ray* ray) override;


	// Inherited via T_racer_Light_Base
	virtual T_racer_Path_Vertex SamplePoint(float& pdf) override;

};