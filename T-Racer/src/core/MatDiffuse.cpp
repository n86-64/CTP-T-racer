#include "helpers/Math_Ray.h"
#include "helpers/Math_Projections.h"
#include "Texture.h"

#include "MatDiffuse.h"

T_racer_Texture2D T_racer_Materials_BasicDiffuse::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex& pathVertex)
{
	T_racer_Math::Colour  lookupColour;
	T_racer_Texture2D  outputTex(1, 1); 

	if (materialTexture) 
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
		lookupColour.colour = lookupColour.colour / (float)M_PI;
		outputTex.copyPixelValues(0, 0, lookupColour.colour.X, lookupColour.colour.Y, lookupColour.colour.Z);
	}

	return outputTex;
}

T_racer_SampledDirection T_racer_Materials_BasicDiffuse::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex)
{
	T_racer_SampledDirection dir;

	T_racer_Math::Vector  samplePos = T_racer_Math::projToUnitDisk(matSampler.Random2());
	samplePos.Z = sqrt(pow(samplePos.X, 2) + pow(samplePos.Y, 2));

	// TODO - Convert to world space using orthonormal basis matrix.

	dir.direction = pathVertex.orthnormalBasis * samplePos;
	dir.probabilityDensity = ProbabilityDensity(ray, dir, pathVertex);

	return dir;
}

float T_racer_Materials_BasicDiffuse::ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex)
{
	return T_racer_Math::dot(sampledDir.direction, pathVertex.normal) / M_PI;
}
