#include "helpers/Math_Ray.h"
#include "helpers/Math_Projections.h"
#include "Texture.h"

#include "MatMirrors.h"

T_racer_Math::Colour T_racer_Materials_Mirror::Evaluate(T_racer_Math::Ray * ray, T_racer_Path_Vertex & pathVertex)
{
	T_racer_Math::Colour  lookupColour;
	T_racer_Texture2D  outputTex(1, 1);

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}

	return lookupColour;
}

T_racer_SampledDirection T_racer_Materials_Mirror::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler& matSampler, T_racer_Path_Vertex& pathVertex)
{


	return T_racer_SampledDirection();
}

float T_racer_Materials_Mirror::ProbabilityDensity(T_racer_Math::Ray* ray, T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex)
{
	return 1.0f;
}
