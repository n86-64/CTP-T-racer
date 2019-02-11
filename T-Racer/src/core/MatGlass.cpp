#include "helpers/Math_neumeric.h"
#include "helpers/Math_Ray.h"

#include "MatGlass.h"

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex & pathVertex)
{
	// Here we aprroximate the colour based on refreaction.
	T_racer_Math::Colour lookupColour;

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}

	T_racer_Math::Vector wo_local = pathVertex.orthnormalBasis * pathVertex.wo;
	float ei = refractiveIndexI, et = refractiveIndexT;
	float cosi = clamp(wo_local.Z, -1.0f, 1.0f);

	T_racer_Math::Colour col = evaluateFresnel(cosi, wo_local, ei, et);
	lookupColour.colour = (lookupColour.colour / cosi) * (T_racer_Math::Colour().colour - col.colour) * ((et*et) / (ei*ei));

	return lookupColour;
}

T_racer_SampledDirection T_racer_Materials_Dilectric_Glass::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex)
{
	// Determine if we need to refract or reflect the light here.
	T_racer_SampledDirection  wi;

	T_racer_Math::Vector wo_local = pathVertex.orthnormalBasis * pathVertex.wo;
	float ei = refractiveIndexI, et = refractiveIndexT;
	float cosi = clamp(wo_local.Z, -1.0f, 1.0f);
	float ratio = (ei / et);

	float sinI2 = sqrtf(fmaxf(0.0f, 1.0f - wo_local.Z* wo_local.Z));
	float sinT2 = ratio * ratio * sinI2;

	float cost = sqrt(fmaxf(0.0f, 1.0f - sinT2));

	if (cosi > 0.0f) { cost = -cost; }

	wi.direction = pathVertex.orthnormalBasis * T_racer_Math::Vector(ratio * -wo_local.X, ratio * -wo_local.Y, cost);
	wi.probabilityDensity = 1.0f; 
	
	return wi;
}

float T_racer_Materials_Dilectric_Glass::ProbabilityDensity(T_racer_Math::Ray * ray, T_racer_SampledDirection & sampledDir, T_racer_Path_Vertex & pathVertex)
{
	return 1.0f;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::evaluateFresnel(float cosi, T_racer_Math::Vector incidentVector, float& ei, float& et)
{
	T_racer_Math::Colour contribution;
	float cosT = 0.0f;

	if (cosi > 0)
	{
		swap(ei, et);
	}
	float sint = (ei / et) * sqrtf(fmaxf(0.0f, 1.0f - cosi * cosi)); // Snells law.

	if (sint > 1.0f)
	{
		// Total internal reflectance. Return strong reflectance.
		return contribution;
	}
	else 
	{
		cosT = sqrtf(fmaxf(0.0f, 1.0f - sint * sint));
		contribution = reflectanceFresnel(cosi, cosT, ei, et);
	}

	return contribution;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::reflectanceFresnel(float cosI, float cosT, float ei, float et)
{
	T_racer_Math::Colour eiCol(ei);
	T_racer_Math::Colour etCol(et);

	T_racer_Math::Colour parallelLight;
	parallelLight.colour = (etCol.colour * cosI) - (eiCol.colour * cosT) / (etCol.colour * cosI) + (eiCol.colour * cosT);
	
	T_racer_Math::Colour purpendicularLight;
	purpendicularLight.colour = (eiCol.colour * cosI) - (etCol.colour * cosT) / (eiCol.colour * cosI) + (etCol.colour * cosT);

	T_racer_Math::Colour returnValue;
	returnValue.colour = ((purpendicularLight.colour * purpendicularLight.colour) + (parallelLight.colour * parallelLight.colour)) * 0.5f;

	return returnValue;
}
