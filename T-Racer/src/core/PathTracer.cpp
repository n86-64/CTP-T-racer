#include "Display.h"
#include "PathTracer.h"

constexpr int  T_RACER_TRIANGLE_NULL = -1;
constexpr float T_RACER_LUMINANCE_VALUE = 0.5f;

constexpr int T_RACER_SAMPLE_COUNT = 1;

constexpr int T_RACER_PATH_INITIAL_COUNT = 20;


T_racer_Renderer_PathTracer::T_racer_Renderer_PathTracer()
{
	// Here we set up the deafault materials.
	materials.retrieveMaterial(0)->setTexture(textures.createTexture("default"));
}

void T_racer_Renderer_PathTracer::Render()
{
	sceneObject->setupScene();

	// Set up a pool of threads and render over multiple threads.
	if (threadCount > 0) 
	{
		std::thread thread;
		for (int i = 0; i < threadCount; i++) 
		{
			thread = std::thread(&T_racer_Renderer_Base::renderThreaded, this);
			thread.detach();
		}

		// Quick and dirty way of waiting for threads to execute.
		while (compleatedTiles != tileCount) 
		{}

		display->update();

		return;
	}

	//int triangleIndex = -1;
	//T_racer_BVH_CollisionQueue_t collisions;
	//T_racer_TriangleIntersection intersectionDisc;

	//T_racer_Math::Colour irradiance;
	//T_racer_Math::Colour lightValue;

	//// Here we trace the ray for the camera.
	//// Generate a ray for each image in the framebuffer.
	//// If intersection with a triangle, colour the pixel else stop. 
	//for (int y = 0; y < display->getHeight(); y++)
	//{
	//	for (int x = 0; x < display->getWidth(); x++)
	//	{
	//		// Here we repeat for N samples and then divide radiance by N samples.
	//		irradiance = T_racer_Math::Colour(1.0f, 1.0f, 1.0f);
	//		lightValue = T_racer_Math::Colour(0.0f, 0.0f, 0.0f);

	//		triangleIndex = sceneObject->traceRay2(x, y, intersectionDisc);

	//		if (triangleIndex != T_RACER_TRIANGLE_NULL) 
	//		{
	//			Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
	//			lightPath.emplace_back(T_racer_Path_Vertex());
	//			lightPath[0].BRDFMaterialID = primative->getMaterialIndex();
	//			lightPath[0].hitPoint = collisions.ray.getHitPoint(intersectionDisc.t);  //primative->getHitPoint(intersectionDisc);
	//			lightPath[0].normal = primative->getNormal().normalise();
	//			lightPath[0].uv = primative->interpolatePoint(intersectionDisc);
	//			lightPath[0].orthnormalBasis = primative->createShadingFrame(lightPath[0].normal);

	//			// Calculate the light paths. Divide result by N value for correct monte carlo estimation. 
	//			tracePath(collisions.ray, irradiance);

	//			for (int i = 0; i < lightPath.size(); i++) 
	//			{
	//				lightValue.colour = lightValue.colour + calculateDirectLighting(&lightPath[i], irradiance).colour;
	//			}

	//		}
	//		lightPath.clear();


	//		display->setColourValue(x, y, lightValue);
	//	}

	//}

	//display->update();
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance)
{
	//T_racer_TriangleIntersection  intersectDisc;
	//T_racer_Material*  surfaceMaterial = nullptr;
	//bool terminatePath = false;

	//T_racer_BVH_CollisionQueue_t  collisions;

	//T_racer_Math::Ray   ray = initialRay;
	//T_racer_Math::Sampler  sampler;

	//T_racer_Math::Colour  pathTroughput;
	//pathTroughput.colour = irradiance.colour;

	//T_racer_SampledDirection  wi;
	//T_racer_Math::Colour  brdfValue;

	//int pathIndex = 0;
	//int triangleIndex = -1;
	//while (!terminatePath) 
	//{
	//	surfaceMaterial = materials.retrieveMaterial(lightPath[pathIndex].BRDFMaterialID);
	//	wi = surfaceMaterial->Sample(&ray, sampler, lightPath[pathIndex]);
	//	brdfValue = surfaceMaterial->Evaluate(&ray, lightPath[pathIndex]).getPixelValue(0,0);

	//	pathTroughput = pathTroughput * brdfValue;
	//	pathTroughput = pathTroughput * T_racer_Math::dot(wi.direction, lightPath[pathIndex].normal);
	//	pathTroughput = pathTroughput / wi.probabilityDensity;

	////	pathTroughput = ((pathTroughput * brdfValue) * T_racer_Math::dot(wi.direction, lightPath[pathIndex].normal)) / wi.probabilityDensity;
	//	terminatePath = !RussianRoulette(pathTroughput, &lightPath[pathIndex]);

	//	lightPath[pathIndex].pathColour = pathTroughput;

	//	// else trace the scene again.
	//	// If we hit a light source also terminate the path.
	//	// then loop.
	//	if (!terminatePath) 
	//	{
	//		//collisions = sceneObject->traceRay(lightPath[pathIndex].hitPoint, wi.direction);
	//		//triangleIndex = sortTriangles(collisions, intersectDisc);

	//		triangleIndex = sceneObject->traceRay2(lightPath[pathIndex].hitPoint, wi.direction, INFINITY, intersectDisc);

	//		// TODO - Add routiene to check if this is a light source.
	//		// If so terminate else we will evaluate the next light path.
	//		if (triangleIndex != -1) 
	//		{
	//			// Create a new light path.
	//			pathIndex++;

	//			// Add to the light index.
	//			Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
	//			lightPath.emplace_back(T_racer_Path_Vertex());
	//			lightPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
	//			lightPath[pathIndex].hitPoint =  collisions.ray.getHitPoint(intersectDisc.t); // primative->getHitPoint(intersectDisc);
	//			lightPath[pathIndex].wo = collisions.ray.getincomingRayDirection();
	//			lightPath[pathIndex].normal = primative->getNormal().normalise();
	//			lightPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
	//			lightPath[pathIndex].orthnormalBasis = primative->createShadingFrame(lightPath[pathIndex].normal);
	//			lightPath[pathIndex].pathColour = pathTroughput;

	//			ray = collisions.ray;
	//		}
	//		else 
	//		{
	//			terminatePath = true;
	//		}
	//	}
	//}

	//irradiance = pathTroughput;
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath)
{
	T_racer_TriangleIntersection  intersectDisc;
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = false;

	T_racer_BVH_CollisionQueue_t  collisions;

	T_racer_Math::Ray   ray = initialRay;
	T_racer_Math::Sampler  sampler;

	T_racer_Math::Colour  pathTroughput;
	pathTroughput.colour = irradiance.colour;

	T_racer_SampledDirection  wi;
	T_racer_Math::Colour  brdfValue;

	int pathIndex = 0;
	int triangleIndex = -1;
	while (!terminatePath)
	{
		surfaceMaterial = materials.retrieveMaterial(lightPath[pathIndex].BRDFMaterialID);
		wi = surfaceMaterial->Sample(&ray, sampler, lightPath[pathIndex]);
		brdfValue = surfaceMaterial->Evaluate(&ray, lightPath[pathIndex]).getPixelValue(0, 0);

		pathTroughput = pathTroughput * brdfValue;
		pathTroughput = pathTroughput * T_racer_Math::dot(wi.direction, lightPath[pathIndex].normal);
		pathTroughput = pathTroughput / wi.probabilityDensity;

		//	pathTroughput = ((pathTroughput * brdfValue) * T_racer_Math::dot(wi.direction, lightPath[pathIndex].normal)) / wi.probabilityDensity;
		terminatePath = !RussianRoulette(pathTroughput, &lightPath[pathIndex]);

		lightPath[pathIndex].pathColour = pathTroughput;

		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
		if (!terminatePath)
		{
			//collisions = sceneObject->traceRay(lightPath[pathIndex].hitPoint, wi.direction);
			//triangleIndex = sortTriangles(collisions, intersectDisc);

			triangleIndex = sceneObject->traceRay2(lightPath[pathIndex].hitPoint, wi.direction, INFINITY, intersectDisc);

			// TODO - Add routiene to check if this is a light source.
			// If so terminate else we will evaluate the next light path.
			if (triangleIndex != -1)
			{
				// Create a new light path.
				pathIndex++;

				// Add to the light index.
				Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
				lightPath.emplace_back(T_racer_Path_Vertex());
				lightPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
				lightPath[pathIndex].hitPoint = collisions.ray.getHitPoint(intersectDisc.t); // primative->getHitPoint(intersectDisc);
				lightPath[pathIndex].wo = collisions.ray.getincomingRayDirection();
				lightPath[pathIndex].normal = primative->getNormal().normalise();
				lightPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
				lightPath[pathIndex].orthnormalBasis = primative->createShadingFrame(lightPath[pathIndex].normal);
				lightPath[pathIndex].pathColour = pathTroughput;

				ray = collisions.ray;
			}
			else
			{
				terminatePath = true;
			}
		}
	}

	irradiance = pathTroughput;
}

void T_racer_Renderer_PathTracer::renderThreaded()
{
	// Data types for rendering threaded.
	T_racer_TriangleIntersection intersectionDisc;
	T_racer_BVH_CollisionQueue_t collisions;

	T_racer_Math::Colour irradiance;
	T_racer_Math::Colour lightValue;

	std::vector<T_racer_Path_Vertex>  lightPath;
	lightPath.reserve(T_RACER_PATH_INITIAL_COUNT);

	int triangleIndex = -1;
	int tWidth;
	int tHeight;

	{
		std::lock_guard<std::mutex>  lock_guard(mtx);
		// Defines the presence of the tiles.
		tWidth = display->getWidth();
		tHeight = display->getHeight();
	}

	while (currentTile < tHeight) 
	{
		int tX = 0;
		int tY = currentTile;
		currentTile++;

		for (tX; tX < tWidth; tX++)
		{
			irradiance = T_racer_Math::Colour(1.0f, 1.0f, 1.0f);
			lightValue = T_racer_Math::Colour(0.0f, 0.0f, 0.0f);

			// Here we render the object.
			mtx.lock();
			triangleIndex = sceneObject->traceRay2(tX, tY, intersectionDisc);

			if (triangleIndex != T_RACER_TRIANGLE_NULL)
			{
				Triangle* primative = sceneObject->getTriangleByIndex(triangleIndex);
				lightPath.emplace_back(T_racer_Path_Vertex());
				lightPath[0].BRDFMaterialID = primative->getMaterialIndex();
				lightPath[0].hitPoint = collisions.ray.getHitPoint(intersectionDisc.t);
				lightPath[0].normal = primative->getNormal().normalise();
				lightPath[0].uv = primative->interpolatePoint(intersectionDisc);
				lightPath[0].orthnormalBasis = primative->createShadingFrame(lightPath[0].normal);

				// Calculate the light paths. Divide result by N value for correct monte carlo estimation. 
				tracePath(collisions.ray, irradiance);

				for (int i = 0; i < lightPath.size(); i++)
				{
					lightValue.colour = lightValue.colour + calculateDirectLighting(&lightPath[i], irradiance).colour;
				}
			}

			lightPath.clear();

			display->setColourValue(tX, tY, lightValue);
			mtx.unlock();

		}

		compleatedTiles++;
	}

	return;
}

// Weight the value according to the luminance if the luminance is less than a random value.
bool T_racer_Renderer_PathTracer::RussianRoulette(T_racer_Math::Colour& colour, T_racer_Path_Vertex* pathIndex)
{
	T_racer_Math::Sampler   sampler;
	float stopProbability = sampler.Random();
	bool rr = (stopProbability >= T_RACER_LUMINANCE_VALUE); // TODO - Add code to perform russian roullete.

	if (rr) 
	{
		colour.colour = colour.colour * (1.0f / 1.0f - stopProbability);
	}

	return rr;
}

T_racer_Math::Colour T_racer_Renderer_PathTracer::calculateDirectLighting(T_racer_Path_Vertex* pathVertex, T_racer_Math::Colour& col)
{
	T_racer_Math::Ray  lightRay;
	T_racer_Math::Colour Ld;
	T_racer_Math::Sampler sampler;
	T_racer_Path_Vertex  lightSourcePath;
	
	T_racer_Material* material = materials.retrieveMaterial(pathVertex->BRDFMaterialID);
	T_racer_Light_Base* lightSource = sceneObject->retrieveOneLightSource(); // Picks out a random light source to sample.

	T_racer_SampledDirection brdf_wi = material->Sample(nullptr, sampler, *pathVertex);
	lightRay = T_racer_Math::Ray(pathVertex->hitPoint, brdf_wi.direction);

	T_racer_SampledDirection light_wi = lightSource->Sample(*pathVertex, lightRay, lightSourcePath);

	float visible = (float)isLightVisible(lightSource, pathVertex);
	float gTerm = geometryTerm(light_wi, brdf_wi, pathVertex, lightSource, lightSourcePath);

	// assert(visible != 0.0f);

	T_racer_Math::Colour brdfLightValue = lightSource->Evaluate(*pathVertex);
	T_racer_Math::Colour brdfSurfaceValue = material->Evaluate(&lightRay, *pathVertex).getPixelValue(0, 0);

	Ld.colour = pathVertex->pathColour.colour * col.colour * brdfLightValue.colour  * brdfSurfaceValue.colour * (visible * gTerm)  / light_wi.probabilityDensity;

	return Ld;
}

// Performs a shadow ray check on the object.
bool T_racer_Renderer_PathTracer::isLightVisible(T_racer_Light_Base* lightSource, T_racer_Path_Vertex* pathVertex)
{
	T_racer_TriangleIntersection intersect;
	T_racer_Math::Vector dir = (lightSource->getPosition() - pathVertex->hitPoint);
	int intersectionIndex = sceneObject->traceRay2(pathVertex->hitPoint, dir.normalise(), dir.Magnitude(), intersect);
	return (intersectionIndex == T_RACER_TRIANGLE_NULL);
}

// Geometry term depends on the light source in question.
float T_racer_Renderer_PathTracer::geometryTerm(T_racer_SampledDirection& Light_wi, T_racer_SampledDirection& brdf_wi, T_racer_Path_Vertex* pathVertex, T_racer_Light_Base* lightSource, T_racer_Path_Vertex& lightVertex)
{
	float brdfTheta = T_racer_Math::dot(brdf_wi.direction, pathVertex->normal);
	float lightTheta = lightSource->surfaceCosine(lightVertex);

	T_racer_Math::Vector xN = pathVertex->hitPoint;
	T_racer_Math::Vector xL = lightVertex.hitPoint;

	return (brdfTheta * lightTheta) / pow((xL-xN).Magnitude(), 2);
}
