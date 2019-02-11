#include "helpers/Math_Ray.h"

#include "MatGlass.h"

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex & pathVertex)
{
	// Here we aprroximate snells law. 

	T_racer_Math::Colour lookupColour;

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}

	// Check if we are refracting or reflecting. 



	return lookupColour;
}

T_racer_SampledDirection T_racer_Materials_Dilectric_Glass::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex)
{
	// Determine if we need to refract or reflect the light here.
	T_racer_SampledDirection  wi;

	T_racer_Math::Vector reflectance = ray->direction; 
	reflectance = reflectance - (pathVertex.normal * 2 * T_racer_Math::dot(pathVertex.normal, reflectance));



	wi.probabilityDensity = ProbabilityDensity(ray, wi, pathVertex); 

	
	return wi;
}

float T_racer_Materials_Dilectric_Glass::ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection & sampledDir, T_racer_Path_Vertex & pathVertex)
{
	return 1.0f;
}
