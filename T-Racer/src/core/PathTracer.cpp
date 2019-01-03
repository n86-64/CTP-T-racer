#include "Display.h"

#include "PathTracer.h"

void T_racer_Renderer_PathTracer::Render()
{
	int triangleIndex = -1;
	T_racer_BVH_CollisionQueue_t collisions;
	T_racer_TriangleIntersection intersectionDisc;

	sceneObject->setupScene();

	// Here we trace the ray for the camera.
	// Generate a ray for each image in the framebuffer.
	// If intersection with a triangle, colour the pixel else stop. 
	for (int y = 0; y < display->getHeight(); y++)
	{
		for (int x = 0; x < display->getWidth(); x++)
		{
			collisions = sceneObject->traceRay(x, y);
			triangleIndex = sortTriangles(collisions, intersectionDisc);

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
				tracePath(collisions.ray);

			}
		}
	}
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay)
{
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = false;

	T_racer_Math::Ray   ray = initialRay;
	T_racer_Math::Sampler  sampler;

	T_racer_Math::Colour  pathTroughput;
	pathTroughput.colour = T_racer_Math::Vector(1.0f, 1.0f, 1.0f);
	T_racer_SampledDirection  wi;

	T_racer_Math::Colour  brdfValue;

	int pathIndex = 0;
	while (!terminatePath) 
	{
		surfaceMaterial = materials.retrieveMaterial(pathIndex);
		wi = surfaceMaterial->Sample(&ray, sampler);

		pathTroughput = pathTroughput * brdfValue * dot(wi.direction, lightPath[pathIndex].normal) / wi.probabilityDensity;
		terminatePath = RussianRoulette(pathTroughput, pathIndex);

		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
	}

}

int T_racer_Renderer_PathTracer::sortTriangles(T_racer_BVH_CollisionQueue_t& collisions, T_racer_TriangleIntersection& intersection)
{
	T_racer_TriangleIntersection intersect;

	int        primaryTriangle = -1;
	float	   tVal = INFINITY;

	// TODO - Move into a seperate routiene.
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

bool T_racer_Renderer_PathTracer::RussianRoulette(T_racer_Math::Colour& colour, int pathIndex)
{
	bool stop = false;


	return stop;
}
