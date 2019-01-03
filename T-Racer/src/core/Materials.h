/** @file Materials.h
*  @brief A basic material definition.
*
*  A base abstract object which contains all the functions that will be used in the creation
*   of materials.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "helpers/Math_Sampler.h"
#include "Texture.h"

namespace T_racer_Math 
{
	class Ray;
}

// The direction the ray should travel along with the probibility density.
struct T_racer_SampledDirection
{
	T_racer_Math::Vector direction;
	float				 probabilityDensity;
};


class T_racer_Material 
{
public:
	T_racer_Material() = default;

	virtual T_racer_Texture2D		 Evaluate(T_racer_Math::Ray* ray) = 0;
	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler) = 0;
	virtual float					 ProbabilityDensity(T_racer_Math::Ray* ray) = 0;

protected:
	T_racer_Texture2D*				 materialTexture = nullptr;
};
