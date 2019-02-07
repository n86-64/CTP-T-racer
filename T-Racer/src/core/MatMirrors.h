/** @file MatMirrors.h
*  @brief A Mirror material.
*
*  A mirror BRDF value which is designed to reflect light bounces.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "Materials.h"

class T_racer_Materials_Mirror : public T_racer_Material 
{
public:
	T_racer_Materials_Mirror() = default;

	// Inherited via T_racer_Material
	virtual T_racer_Math::Colour Evaluate(T_racer_Math::Ray * ray, T_racer_Path_Vertex& pathVertex) override;
	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex) override;
	virtual float ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex) override;
};