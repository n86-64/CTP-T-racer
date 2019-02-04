#include "helpers/Math_Trig.h"
#include "PointLight.h"

T_racer_Math::Colour T_racer_Light_Point::Evaluate(T_racer_Path_Vertex & pathVertex)
{	
	return intensity;
}

T_racer_SampledDirection T_racer_Light_Point::Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay, T_racer_Path_Vertex& lightSourcePath)
{
	lightSourcePath.hitPoint = position;

	T_racer_SampledDirection dir;
	dir.direction = (position - inputRay.getPosition()).normalise();
	dir.probabilityDensity = probabilityDensity(pathVertex, inputRay);

	return dir;
}

float T_racer_Light_Point::probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray & inputRay)
{
	// PDF derived from PBRT (p.g. 697)
	return 1.0f;
}

float T_racer_Light_Point::surfaceCosine(T_racer_Path_Vertex& vertex)
{
	return 1.0f;
}
