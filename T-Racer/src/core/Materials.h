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
#include "SampledObjects.h"
#include "PathVertex.h"

namespace T_racer_Math 
{
	class Ray;
}

class T_racer_Material 
{
public:
	T_racer_Material() = default;

	virtual T_racer_Math::Colour	 Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex& pathVertex) = 0;
	virtual T_racer_Math::Colour	 Evaluate2(T_racer_SampledDirection& wi, T_racer_Path_Vertex& pathVertex) { return T_racer_Math::Colour(0, 0, 0); }
	virtual T_racer_SampledDirection Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex) = 0;
	virtual T_racer_Math::Colour     SampleMaterial(T_racer_Math::Sampler& matSampler, T_racer_SampledDirection& wi, T_racer_Path_Vertex& pathVertex) { return T_racer_Math::Colour(0,0,0); }
	virtual float					 ProbabilityDensity(T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex) = 0;

	std::string getName() const { return name; }
	void		setName(std::string value) { name = value; }

	void	    setTexture(T_racer_Texture2D* newTexture);

	T_racer_Math::Colour			 albedo = T_racer_Math::Colour(1, 1, 1);

protected:
	std::string						 name = "default";
	T_racer_Texture2D*				 materialTexture = nullptr;

};
