#include "Display.h"

#include "PathTracer.h"

constexpr float T_RACER_LUMINANCE_VALUE = 0.5f;


void T_racer_Renderer_PathTracer::Render()
{
	int triangleIndex = -1;
	T_racer_BVH_CollisionQueue_t collisions;
	T_racer_TriangleIntersection intersectionDisc;

	T_racer_Math::Colour irradiance;

	sceneObject->setupScene();

	// Here we trace the ray for the camera.
	// Generate a ray for each image in the framebuffer.
	// If intersection with a triangle, colour the pixel else stop. 
	for (int y = 0; y < display->getHeight(); y++)
	{
		for (int x = 0; x < display->getWidth(); x++)
		{
			// Here we repeat for N samples and then divide radiance by N samples.

			collisions = sceneObject->traceRay(x, y);
			triangleIndex = sortTriangles(collisions, intersectionDisc);

			if (triangleIndex >= 0) 
			{
				display->setColourValue(x, y, T_racer_Math::Colour(1.0f,1.0f,1.0f));
			}
			else 
			{
				display->setColourValue(x, y, T_racer_Math::Colour(0.0f, 0.0f, 0.0f));
			}

#ifdef FALSE
			if (triangleIndex) 
			{
				Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
				lightPath.emplace_back(T_racer_Path_Vertex());
				lightPath[0].BRDFMaterialID = primative->getMaterialIndex();
				lightPath[0].hitPoint = collisions.ray.getHitPoint(intersectionDisc.t);
				lightPath[0].normal = primative->getNormal();
				lightPath[0].uv = primative->interpolatePoint(intersectionDisc);
				lightPath[0].orthnormalBasis = primative->createShadingFrame();

				// Calculate the light paths.
				tracePath(collisions.ray, irradiance);

			}
#endif
		}
	}
	display->update();
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance)
{
	T_racer_TriangleIntersection  intersectDisc;
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = false;

	T_racer_BVH_CollisionQueue_t  collisions;

	T_racer_Math::Ray   ray = initialRay;
	T_racer_Math::Sampler  sampler;

	T_racer_Math::Colour  pathTroughput;

	pathTroughput.colour = T_racer_Math::Vector(1.0f, 1.0f, 1.0f);
	T_racer_SampledDirection  wi;

	T_racer_Math::Colour  brdfValue;

	int pathIndex = 0;
	int triangleIndex = -1;
	while (!terminatePath) 
	{
		surfaceMaterial = materials.retrieveMaterial(lightPath[pathIndex].BRDFMaterialID);
		wi = surfaceMaterial->Sample(&ray, sampler, lightPath[pathIndex]);

		pathTroughput = pathTroughput * brdfValue * dot(wi.direction, lightPath[pathIndex].normal) / wi.probabilityDensity;
		terminatePath = RussianRoulette(pathTroughput, pathIndex);

		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
		if (!terminatePath) 
		{
			collisions = sceneObject->traceRay(lightPath[pathIndex].hitPoint, wi.direction);
			triangleIndex = sortTriangles(collisions, intersectDisc);

			// TODO - Add routiene to check if this is a light source.
			// If so terminate else we will evaluate the next light path.
			if (triangleIndex) 
			{
				// Create a new light path.
				pathIndex++;

				// Add to the light index.
				Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
				lightPath.emplace_back(T_racer_Path_Vertex());
				lightPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
				lightPath[pathIndex].hitPoint = collisions.ray.getHitPoint(intersectDisc.t);
				lightPath[pathIndex].normal = primative->getNormal();
				lightPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
				lightPath[pathIndex].orthnormalBasis = primative->createShadingFrame();
			}
			else 
			{
				terminatePath = true;
			}
		}
	}

}

int T_racer_Renderer_PathTracer::sortTriangles(T_racer_BVH_CollisionQueue_t& collisions, T_racer_TriangleIntersection& intersection)
{
	T_racer_TriangleIntersection intersect;

	int        primaryTriangle = -1;
	float	   tVal = INFINITY;

	for (int pIndex : collisions.triangleIndexes)
	{
		intersect = sceneObject->getTriangleByIndex(pIndex)->isIntersecting(collisions.ray);
		if (intersect.t < tVal)
		{
			primaryTriangle = pIndex;
			tVal = intersect.t;
			intersection = intersect;
		}
	}

	return primaryTriangle;
}

// Weight the value according to the luminance if the luminance is less than a random value.
bool T_racer_Renderer_PathTracer::RussianRoulette(T_racer_Math::Colour& colour, int pathIndex)
{
	T_racer_Math::Sampler   sampler;
	bool rr = (sampler.Random() < T_RACER_LUMINANCE_VALUE); // TODO - Add code to perform russian roullete.

	if (rr) 
	{
		colour.colour = colour.colour / (colour.colour * T_RACER_LUMINANCE_VALUE);
	}

	return rr;
}

T_racer_Math::Colour T_racer_Renderer_PathTracer::calculateDirectLighting(int pathVertex, T_racer_Math::Colour& col)
{
	T_racer_Light_Base* lightSource = sceneObject->sampleOneLightSource();
	sceneObject->traceRay(lightPath[pathVertex].hitPoint, lightSource->getPosition().normalise());
	T_racer_Material* material = materials.retrieveMaterial(lightPath[pathVertex].BRDFMaterialID);
	return col;
}

bool T_racer_Renderer_PathTracer::isLightVisible()
{

	return true;
}
