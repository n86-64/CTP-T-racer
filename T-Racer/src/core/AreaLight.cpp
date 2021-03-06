#include "helpers/Math_Sampler.h"
#include "helpers/Math_Projections.h"
#include "helpers/Math_Error.h"

#include "AreaLight.h"


T_racer_Light_Area::T_racer_Light_Area()
{
}

T_racer_Math::Colour T_racer_Light_Area::Evaluate(T_racer_Path_Vertex& pathVertex)
{
	return T_racer_Math::dot(pathVertex.normal, pathVertex.wo) > T_RACER_EPSILON ? intensity : T_racer_Math::Colour(0,0,0);
}

T_racer_SampledDirection T_racer_Light_Area::Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray & inputRay, T_racer_Path_Vertex & lightSourceVertex)
{
	srand(NULL);
	int triIndex = 0; //rand() % triangles.size();

	T_racer_Math::Sampler  sampler;
	triIndex = sampler.RandomRange(0, triangles.size() - 1);

	T_racer_SampledDirection wi;

	lightSourceVertex.isPointLightSource = false;
	lightSourceVertex.normal = triangles[triIndex].getNormal();
			
	lightSourceVertex.hitPoint = triangles[triIndex].samplePoint();
	wi.direction = (pathVertex.hitPoint - lightSourceVertex.hitPoint).normalise();  

	wi.probabilityDensityArea = 1 / triangles[triIndex].getSurfaceArea();
	wi.probabilityDensity = wi.probabilityDensityArea;
	wi.direction.normaliseSelf();

	pdfDirection = wi.probabilityDensity;

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

T_racer_Math::Vector T_racer_Light_Area::getLightSurfaceNormal(int surfaceIndex)
{
	return triangles[surfaceIndex].getNormal();
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

	return bestIntersection;
}

T_racer_Path_Vertex T_racer_Light_Area::SamplePoint(float& pdf)
{
	srand(NULL);
	int triIndex = 0; // rand() % triangles.size();

	T_racer_Math::Sampler sampler;
	triIndex = sampler.RandomRange(0, triangles.size() - 1);

	T_racer_Path_Vertex initLightPath;
	initLightPath.hitPoint = triangles[triIndex].samplePoint();
	initLightPath.isOnLightSource = true;
	initLightPath.normal = triangles[triIndex].normal;
	initLightPath.orthnormalBasis = triangles[triIndex].createShadingFrame(initLightPath.normal);
	pdf *= (1 / triangles[triIndex].getSurfaceArea());

	return initLightPath;
}

T_racer_SampledDirection T_racer_Light_Area::SampleDirection(T_racer_Math::Sampler* sampler, T_racer_Path_Vertex* pathVertex)
{
	T_racer_Math::Vector sampleDir;
	sampleDir = T_racer_Math::projToUnitDisk(sampler->Random2());
	sampleDir.Z = sqrt(1.0f - ((sampleDir.X * sampleDir.X) + (sampleDir.Y * sampleDir.Y)));

	T_racer_SampledDirection wi;
	wi.direction = T_racer_Math::transposeMatrix3x3(pathVertex->orthnormalBasis) * sampleDir;
	wi.probabilityDensity = fabsf(T_racer_Math::dot(wi.direction, pathVertex->normal)) / M_PI;

	return wi;
}

void T_racer_Light_Area::init(jsoncons::key_value<std::string, jsoncons::json>& initValues)
{
	// Get array of triangles here. 
	int size = initValues.value()["NumberOfVertices"].as_int();
	triangles.reserve((int)size / 3);

	T_racer_Vertex  v[3];
	for (int i = 0; i < size; i++) 
	{
		if (i % 3 == 0 && i != 0)
		{
			triangles.emplace_back(v[0], v[1], v[2]);
		}

		v[i % 3].position = T_racer_Math::Vector(initValues.value()["Vertices"][i][0].as_double(),
			initValues.value()["Vertices"][i][1].as_double(),
			initValues.value()["Vertices"][i][2].as_double());
	}

	triangles.emplace_back(v[0], v[1], v[2]);

	intensity.colour = T_racer_Math::Vector( initValues.value()["Intensity"][0].as_double(), initValues.value()["Intensity"][1].as_double(), initValues.value()["Intensity"][2].as_double());
}
