#include "helpers/Math_Sampler.h"
#include "helpers/Math_Projections.h"

#include "AreaLight.h"


T_racer_Light_Area::T_racer_Light_Area()
{
	intensity.colour = T_racer_Math::Vector(1, 1, 1);
}

T_racer_Math::Colour T_racer_Light_Area::Evaluate(T_racer_Path_Vertex& pathVertex)
{
	return T_racer_Math::dot(pathVertex.normal, pathVertex.wi) > 0 ? intensity : T_racer_Math::Colour(0,0,0);
}

T_racer_SampledDirection T_racer_Light_Area::Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex & lightSourceVertex)
{
	T_racer_Math::Sampler  sampler;
	T_racer_SampledDirection wi;

	lightSourceVertex.isPointLightSource = false;

	for (int i = 0; i < triangles.size(); i++) 
	{
		if (triangles[i].isIntersecting(&inputRay).intersection) 
		{
			T_racer_Math::Vector samplePos = T_racer_Math::projToUnitDisk(sampler.Random2());
			samplePos.Z = sqrt((samplePos.X * samplePos.X) + (samplePos.Y * samplePos.Y));
			
			lightSourceVertex.hitPoint = triangles[i].samplePoint();
			wi.direction = pathVertex.orthnormalBasis * samplePos;
			wi.probabilityDensity = probabilityDensity(pathVertex, inputRay);
			wi.probabilityDensityArea = 1 / triangles[i].getSurfaceArea();
			wi.direction.normaliseSelf();
			pdfDirection = wi.probabilityDensity;

			return wi;
		}
	}

	// Here we account for cases where the ray intersects with no light. 
	return wi;
}

float T_racer_Light_Area::probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay)
{
	return T_racer_Math::dot(inputRay.direction, pathVertex.normal) / M_PI;
}

float T_racer_Light_Area::surfaceCosine(T_racer_Path_Vertex & vertex)
{
	return 0.0f;
}

T_racer_TriangleIntersection T_racer_Light_Area::doesIntersect(T_racer_Math::Ray* ray)
{
	T_racer_TriangleIntersection intersect;
	T_racer_TriangleIntersection bestIntersection;

	for (int i = 0; i < triangles.size(); i++)
	{
		intersect = triangles[i].isIntersecting(ray);
		if (intersect.intersection && intersect.t < bestIntersection.t)
		{
			intersect.lightTriangleID = i;
			bestIntersection = intersect;
		}
	}

	return intersect;
}
