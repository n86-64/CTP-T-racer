#include "PointLight.h"

T_racer_Math::Colour T_racer_Light_Point::Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay)
{
	return intensity / T_racer_Math::dot(position, pathVertex.hitPoint);
}

float T_racer_Light_Point::probabilityDensity(T_racer_Path_Vertex & pathVertex, T_racer_Math::Ray & inputRay)
{
	// PDF derived from PBRT (p.g. 697)
	return 0.0f;
}

T_racer_Math::Colour T_racer_Light_Point::Sample(T_racer_SampledDirection sampledDirection)
{
	return T_racer_Math::Colour();
}
