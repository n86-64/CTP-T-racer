#include "helpers/Math_neumeric.h"
#include "helpers/Math_Ray.h"
#include "helpers/Math_Error.h"

#include "MatGlass.h"

T_racer_Materials_Dilectric_Glass::T_racer_Materials_Dilectric_Glass()
{
	albedo = T_racer_Math::Colour(1.0, 1.0, 1.0);
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::Evaluate(T_racer_Math::Ray* ray, T_racer_Path_Vertex & pathVertex)
{
	// Here we aprroximate the colour based on refreaction.
	T_racer_Math::Colour returnColour; 
	T_racer_Math::Colour lookupColour;

	if (materialTexture)
	{
		lookupColour = materialTexture->interpolatePointBilinear(pathVertex.uv.X, pathVertex.uv.Y);
	}
	else 
	{
		lookupColour = albedo;
	}

	T_racer_Math::Vector wo_local = pathVertex.orthnormalBasis * pathVertex.wo;
	T_racer_Math::Vector wi_local = pathVertex.orthnormalBasis * ray->direction;
	float ei = refractiveIndexI, et = refractiveIndexT;
	float cosi = clamp(wo_local.Z, -1.0f, 1.0f);

	if (!(wo_local.Z > 0)) { swap(ei, et); }

	T_racer_Math::Colour col = evaluateFresnel(cosi);
	if (wo_local.Z * wi_local.Z > 0)
	{
		returnColour.colour = (lookupColour.colour / fabsf(wi_local.Z));
		return returnColour;
	}
	returnColour.colour = (lookupColour.colour / fabsf(wi_local.Z)) * (T_racer_Math::Colour(1, 1, 1).colour - col.colour) * ((et*et) / (ei*ei));

	return returnColour;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::Evaluate2(T_racer_SampledDirection & wi, T_racer_Path_Vertex & pathVertex)
{
	return T_racer_Math::Colour();
}

T_racer_SampledDirection T_racer_Materials_Dilectric_Glass::Sample(T_racer_Math::Ray* ray, T_racer_Math::Sampler & matSampler, T_racer_Path_Vertex & pathVertex)
{
	// Determine if we need to refract or reflect the light here.
	T_racer_SampledDirection  wi;

	pathVertex.isFresnelSurface = true;

	T_racer_Math::Vector wo_local = pathVertex.orthnormalBasis * pathVertex.wo;

	float ei = refractiveIndexI, et = refractiveIndexT;

	// Evaluate Fresnel
	T_racer_Math::Colour col = evaluateFresnel(wo_local.Z);
	// Sample Reflection or Refraction
	float reflw;
	reflw = col.getLuminance();
	if (matSampler.Random() < reflw)
	{
		wo_local.X = -wo_local.X;
		wo_local.Y = -wo_local.Y;
		wi.direction = T_racer_Math::transposeMatrix3x3(pathVertex.orthnormalBasis) * wo_local;
		wi.probabilityDensity = reflw;
		return wi;
	}

	bool entering = (wo_local.Z > 0.0f);
	if (!entering) { std::swap(ei, et); }

	float ratio = (ei / et);

	float sinI2 = 1.0f - (wo_local.Z * wo_local.Z);
	float sinT2 = ratio * ratio * sinI2;

	if (sinT2 > 1.0f) { return wi; }

	float cost = sqrt(fmaxf(0.0f, 1.0f - sinT2));

	if (entering) { cost = -cost; }

	wi.direction = T_racer_Math::transposeMatrix3x3(pathVertex.orthnormalBasis) * T_racer_Math::Vector(ratio * -wo_local.X, ratio * -wo_local.Y, cost);
	wi.probabilityDensity = 1.0f - reflw;
	
	return wi;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::SampleMaterial(T_racer_Math::Sampler & matSampler, T_racer_SampledDirection & wi, T_racer_Path_Vertex & pathVertex)
{
	pathVertex.isFresnelSurface = true;

	T_racer_Math::Vector wo_local = pathVertex.orthnormalBasis * pathVertex.wo;

	float ei = refractiveIndexI, et = refractiveIndexT;

	// Evaluate Fresnel
	T_racer_Math::Colour col = evaluateFresnel(wo_local.Z);
	// Sample Reflection or Refraction
	float reflw;
	reflw = col.getLuminance();
	if (matSampler.Random() < reflw)
	{
		wo_local.X = -wo_local.X;
		wo_local.Y = -wo_local.Y;
		wi.direction = T_racer_Math::transposeMatrix3x3(pathVertex.orthnormalBasis) * wo_local;
		wi.probabilityDensity = reflw;
		return col;
	}

	bool entering = (wo_local.Z > 0.0f);
	if (!entering) { std::swap(ei, et); }

	float ratio = (ei / et);

	float sinI2 = 1.0f - (wo_local.Z * wo_local.Z);
	float sinT2 = ratio * ratio * sinI2;

	if (sinT2 > 1.0f) { return T_racer_Math::Colour(0,0,0); }

	float cost = sqrtf(fmaxf(0.0f, 1.0f - sinT2));

	if (entering) { cost = -cost; }

	float SinIoverSinT = sinI2 / sinT2;
	SinIoverSinT = sqrtf(SinIoverSinT);

	wi.direction = T_racer_Math::transposeMatrix3x3(pathVertex.orthnormalBasis) * T_racer_Math::Vector(SinIoverSinT * -wo_local.X, SinIoverSinT * -wo_local.Y, cost);
	wi.probabilityDensity = 1.0f - reflw;

	T_racer_Math::Vector  wi_local = pathVertex.orthnormalBasis * wi.direction;
	col.colour = (col.colour / fabsf(wi_local.Z)) * (T_racer_Math::Colour(1, 1, 1).colour - col.colour) * ((et*et) / (ei*ei));

	return col;
}

float T_racer_Materials_Dilectric_Glass::ProbabilityDensity(T_racer_SampledDirection& sampledDir, T_racer_Path_Vertex& pathVertex)
{
	return 1.0f;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::evaluateFresnel(float cosi)
{
	T_racer_Math::Colour contribution;
	float ei = refractiveIndexI, et = refractiveIndexT;

	cosi = clamp(cosi, -1.0f, 1.0f);
	bool entering = cosi > 0.0f;
	if (!entering)
	{
		std::swap(ei, et);
	}

	float sint = (ei / et) * sqrtf(fmaxf(0.0f, 1.0f - cosi * cosi)); // Snells law.

	if (sint > 1.0f)
	{
		// Total internal reflectance. Return strong reflectance.
		return T_racer_Math::Colour(1, 1, 1);
	}
	else 
	{
		float cosT = sqrtf(fmaxf(0.0f, 1.0f - sint * sint));
		contribution = reflectanceFresnel(fabsf(cosi), cosT, ei, et);
	}

	return contribution;
}

T_racer_Math::Colour T_racer_Materials_Dilectric_Glass::reflectanceFresnel(float cosI, float cosT, float ei, float et)
{
	T_racer_Math::Colour eiCol(ei, ei, ei);
	T_racer_Math::Colour etCol(et, et, et);

	T_racer_Math::Colour parallelLight;
	parallelLight.colour = (etCol.colour * cosI) - (eiCol.colour * cosT) / (etCol.colour * cosI) + (eiCol.colour * cosT);
	
	T_racer_Math::Colour purpendicularLight;
	purpendicularLight.colour = (eiCol.colour * cosI) - (etCol.colour * cosT) / (eiCol.colour * cosI) + (etCol.colour * cosT);

	T_racer_Math::Colour returnValue;
	returnValue.colour = ((parallelLight.colour * parallelLight.colour) + (purpendicularLight.colour * purpendicularLight.colour)) * 0.5f;

	return returnValue;
}
