#include "helpers/Math_Ray.h"
#include "helpers/Math_Projections.h"
#include "Texture.h"

#include "MatDiffuse.h"

T_racer_Texture2D T_racer_Materials_BasicDiffuse::Evaluate(T_racer_Math::Ray * ray)
{
	T_racer_Math::Colour  lookupColour;
	T_racer_Texture2D  outputTex(1, 1); 

	if (materialTexture) 
	{
		lookupColour = materialTexture->interpolatePointBilinear(0.0f, 1.0f);
		lookupColour.colour = lookupColour.colour / M_PI;
		outputTex.copyPixelValues(0, 0, lookupColour.colour.X, lookupColour.colour.Y, lookupColour.colour.Z);
	}

	return outputTex;
}

T_racer_SampledDirection T_racer_Materials_BasicDiffuse::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler matSampler)
{
	T_racer_SampledDirection dir;

	T_racer_Math::Vector  samplePos = T_racer_Math::projToUnitDisk(matSampler.Random2());
	samplePos.Z = sqrt(pow(samplePos.X, 2) + pow(samplePos.Y, 2));

	// TODO - Convert to world space using orthonormal basis matrix.

	dir.direction = samplePos;
	dir.probabilityDensity = ProbabilityDensity(ray);

	return dir;
}

float T_racer_Materials_BasicDiffuse::ProbabilityDensity(T_racer_Math::Ray * ray)
{
	T_racer_SampledDirection sampledDirection;

	return 0.0f;
}
