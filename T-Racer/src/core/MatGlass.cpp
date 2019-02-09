#include "MatGlass.h"

T_racer_Math::Colour T_racer_Materials_Glass::Evaluate(T_racer_Math::Ray * ray, T_racer_Path_Vertex & pathVertex)
{
	// Here we aprroximate snells law. 

	T_racer_Math::Colour lookupColour;

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}

	return lookupColour;
}

T_racer_SampledDirection T_racer_Materials_Glass::Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex)
{

	return T_racer_SampledDirection();
}

float T_racer_Materials_Glass::ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection & sampledDir, T_racer_Path_Vertex & pathVertex)
{
	return 1.0f;
}
