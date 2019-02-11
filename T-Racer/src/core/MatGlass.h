/** @file MatGlass.h
*  @brief A Mirror material.
*
*  A glass BRDF thet implimentes fresnel reflectance for dielectric glass.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "Materials.h"

class T_racer_Materials_Dilectric_Glass : public T_racer_Material 
{
public:
	T_racer_Materials_Dilectric_Glass() = default;

	// Inherited via T_racer_Material
	virtual T_racer_Math::Colour Evaluate(T_racer_Math::Ray * ray, T_racer_Path_Vertex & pathVertex) override;
	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex) override;
	virtual float ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection & sampledDir, T_racer_Path_Vertex & pathVertex) override;

private:
	T_racer_Math::Colour shlickApproximation(T_racer_Math::Ray* incidentRay, T_racer_Math::Vector normal);
	bool refracting(T_racer_Math::Ray* incidentRay, T_racer_Math::Vector normal);

private:
	float refractiveIndex = 1.5f; // The material refractive index. (for air n = 1)


	T_racer_Math::Colour annuation = T_racer_Math::Colour(1.0f, 1.0f, 0.0f);
	T_racer_Math::Colour absorbtionCoeficcent = T_racer_Math::Colour(1.0f, 1.0f, 1.0f); 
};