#include "helpers/Math_Ray.h"
#include "helpers/Math_Projections.h"

#include "MatDiffuse.h"

T_racer_Math::Colour T_racer_Materials_BasicDiffuse::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex& pathVertex)
{
	T_racer_Math::Colour  lookupColour;
	T_racer_Texture2D  outputTex(1, 1); 

	if (materialTexture) 
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
		//outputTex.copyPixelValues(0, 0, lookupColour.colour.X, lookupColour.colour.Y, lookupColour.colour.Z);
	}
	else 
	{
		lookupColour = albedo;
	}

	lookupColour.colour = lookupColour.colour / (float)M_PI;

	return lookupColour;
}

T_racer_SampledDirection T_racer_Materials_BasicDiffuse::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex)
{
	T_racer_SampledDirection dir;

	T_racer_Math::Vector  samplePos = T_racer_Math::projToUnitDisk(matSampler.Random2());
	samplePos.Z = sqrt(1.0f - ((samplePos.X * samplePos.X) + (samplePos.Y * samplePos.Y)));

	// TODO - Convert to world space using orthonormal basis matrix.
	dir.direction = T_racer_Math::transposeMatrix3x3(pathVertex.orthnormalBasis) * samplePos;
	dir.direction.normaliseSelf();
	dir.probabilityDensity = ProbabilityDensity(ray, dir, pathVertex);
	
	return dir;
}

float T_racer_Materials_BasicDiffuse::ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex)
{
	return abs(T_racer_Math::dot(sampledDir.direction, pathVertex.normal)) / M_PI;
}
