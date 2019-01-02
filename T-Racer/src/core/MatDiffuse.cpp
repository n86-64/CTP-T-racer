#include "MatDiffuse.h"

T_racer_Texture2D T_racer_Materials_BasicDiffuse::Evaluate(T_racer_Math::Ray * ray)
{
	T_racer_Texture2D(1, 1);



	return T_racer_Texture2D();
}

T_racer_SampledDirection T_racer_Materials_BasicDiffuse::Sample(T_racer_Math::Ray * ray, T_racer_Math::Sampler matSampler)
{


	return T_racer_SampledDirection();
}

float T_racer_Materials_BasicDiffuse::ProbabilityDensity(T_racer_Math::Ray * ray)
{
	T_racer_SampledDirection sampledDirection;

	return 0.0f;
}
