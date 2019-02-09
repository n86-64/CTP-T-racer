#include <cassert>
#include <iostream>
#include <string>
#include "helpers/Math_Ray.h"

#include "MatMirrors.h"

T_racer_Math::Colour T_racer_Materials_Mirror::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex& pathVertex)
{
	T_racer_Math::Colour  lookupColour;

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}

	T_racer_Math::Vector halfVector = (ray->direction + pathVertex.wo).normalise();
	float value = T_racer_Math::dot(halfVector, pathVertex.normal);

	if (value > FLT_EPSILON) 
	{
		return lookupColour;
	}

	//T_racer_Math::Vector v = ray->direction - pathVertex.normal * 2 * pathVertex.normal * T_racer_Math::dot(ray->direction, pathVertex.normal); 
	
	return T_racer_Math::Colour(0,0,0);
}

T_racer_SampledDirection T_racer_Materials_Mirror::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex)
{
	T_racer_SampledDirection  wi;
	T_racer_Math::Vector transformedRayDirection = ray->direction; //pathVertex.orthnormalBasis * ray->getincomingRayDirection();
	
	transformedRayDirection = transformedRayDirection - (pathVertex.normal * 2 * T_racer_Math::dot(pathVertex.normal, transformedRayDirection));

	wi.direction = transformedRayDirection;
	wi.probabilityDensity = ProbabilityDensity(ray, wi, pathVertex);

	return wi;
}

float T_racer_Materials_Mirror::ProbabilityDensity(T_racer_Math::Ray* ray, T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex)
{
	return 1.0f;
}
