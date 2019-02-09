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

class T_racer_Materials_Glass : public T_racer_Material 
{
public:
	T_racer_Materials_Glass() = default;

	// Inherited via T_racer_Material
	virtual T_racer_Math::Colour Evaluate(T_racer_Math::Ray * ray, T_racer_Path_Vertex & pathVertex) override;
	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex) override;
	virtual float ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection & sampledDir, T_racer_Path_Vertex & pathVertex) override;

private:
	float refractiveIndex = 1.5f; // The material refractive index. 
	bool refracting = false;
};