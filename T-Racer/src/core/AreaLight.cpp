#include "AreaLight.h"

T_racer_Math::Colour T_Racer_Light_Area::Evaluate(T_racer_Path_Vertex & pathVertex)
{

	return T_racer_Math::Colour();
}

T_racer_SampledDirection T_Racer_Light_Area::Sample(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex & lightSourceVertex)
{
	T_racer_SampledDirection wi;

	for (int i = 0; i < triangles.size(); i++) 
	{
		if (triangles[i].isIntersecting(&inputRay).intersection) 
		{
			pdfPoint = 1 / triangles[i].getSurfaceArea();
		}
	}

	return T_racer_SampledDirection();
}

float T_Racer_Light_Area::probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay)
{
	return 0.0f;
}

float T_Racer_Light_Area::surfaceCosine(T_racer_Path_Vertex & vertex)
{
	return 0.0f;
}