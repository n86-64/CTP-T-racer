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
				tracePath();


			}
		}
	}
}

void T_racer_Renderer_PathTracer::tracePath()
{
	
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
