/** @file MatDiffuse.h
*  @brief A basic diffuse material.
*
*  Describes a diffuse material.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "Materials.h"

class T_racer_Materials_BasicDiffuse : public T_racer_Material
{
public:
	T_racer_Materials_BasicDiffuse() = default;

	// Inherited via T_racer_Material
	virtual T_racer_Texture2D Evaluate(T_racer_Math::Ray * ray) override;

	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler matSampler) override;

	virtual float ProbabilityDensity(T_racer_Math::Ray * ray) override;

};
