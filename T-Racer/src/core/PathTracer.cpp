#include "Display.h"
#include "PathTracer.h"

constexpr int  T_RACER_TRIANGLE_NULL = -1;
constexpr float T_RACER_LUMINANCE_VALUE = 0.1f;

constexpr int T_RACER_SAMPLE_COUNT = 2000;

constexpr int T_RACER_PATH_INITIAL_COUNT = 20;

constexpr int T_RACER_MINIMUM_BOUNCE = 4; // PBRT derived. 


T_racer_Renderer_PathTracer::T_racer_Renderer_PathTracer()
{
}

void T_racer_Renderer_PathTracer::Render()
{
	sceneObject->setupScene();
	//threadCount = 1;

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
		{
			display->update();
		}

		return;
	}
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance)
{
	
}

void T_racer_Renderer_PathTracer::tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath)
{
	T_racer_TriangleIntersection  intersectDisc;
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = false;

	T_racer_Math::Ray   ray = initialRay;
	T_racer_Math::Sampler  sampler;

	T_racer_Math::Colour  pathTroughput = irradiance;

	T_racer_SampledDirection  wi;
	T_racer_Math::Colour  brdfValue;

	int pathIndex = 0;
	while (!terminatePath)
	{
		surfaceMaterial = sceneObject->materials.retrieveMaterial(lightPath[pathIndex].BRDFMaterialID);
		wi = surfaceMaterial->Sample(&ray, sampler, lightPath[pathIndex]);
		ray = T_racer_Math::Ray(lightPath[pathIndex].hitPoint, wi.direction);
		brdfValue = surfaceMaterial->Evaluate(&ray, lightPath[pathIndex]);

		pathTroughput = pathTroughput * brdfValue;
		pathTroughput = pathTroughput * T_racer_Math::dot(wi.direction, lightPath[pathIndex].normal);
		pathTroughput = pathTroughput / wi.probabilityDensity;


	    lightPath[pathIndex].pathColour = pathTroughput;

		terminatePath = (pathTroughput.colour.X == 0.0f && pathTroughput.colour.Y == 0.0f && pathTroughput.colour.Z == 0.0f);

		if (pathIndex > T_RACER_MINIMUM_BOUNCE) 
		{
			terminatePath = !RussianRoulette(pathTroughput, &lightPath[pathIndex]);
		}


		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
		if (!terminatePath)
		{
			intersectDisc = sceneObject->trace(ray);

			// TODO - Add routiene to check if this is a light source.
			// If so terminate else we will evaluate the next light path.
			if (intersectDisc.triangleID != T_RACER_TRIANGLE_NULL)
			{
				// Create a new light path.
				pathIndex++;

				// Add to the light index.
				Triangle* primative = sceneObject->getTriangleByIndex(intersectDisc.triangleID);
				lightPath.emplace_back(T_racer_Path_Vertex());
				lightPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
				lightPath[pathIndex].hitPoint = lightPath[pathIndex].hitPoint + (wi.direction * intersectDisc.t);
				lightPath[pathIndex].wo = -wi.direction;
				lightPath[pathIndex].normal = primative->getNormal().normalise();
				lightPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
				lightPath[pathIndex].orthnormalBasis = primative->createShadingFrame(lightPath[pathIndex].normal);
				lightPath[pathIndex].pathColour = pathTroughput;

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
	T_racer_Math::Sampler sampler;

	T_racer_Math::Vector bias;

	T_racer_Math::Colour irradiance;
	T_racer_Math::Colour lightValue;
	T_racer_Math::Colour lightSigma;

	std::vector<T_racer_Path_Vertex>  lightPath;
	lightPath.reserve(T_RACER_PATH_INITIAL_COUNT);
	int tWidth;
	int tHeight;

	float width = display->getWidth();
	float height = display->getHeight();

	tWidth = display->getWidth();
	tHeight = display->getHeight();

	while (currentTile < tHeight) 
	{
		int tX = 0;
		int tY = currentTile;
		currentTile++;

		for (tX; tX < tWidth; tX++)
		{
			lightSigma = T_racer_Math::Colour(0.0, 0.0f, 0.0f);

			// Here we render the object.
			for (int i = 0; i < T_RACER_SAMPLE_COUNT; i++)
			{
				//bias = sampler.Random2();
				irradiance = T_racer_Math::Colour(1.0f, 1.0f, 1.0f);
				lightValue = T_racer_Math::Colour(0.0f, 0.0f, 0.0f);

				T_racer_Math::Ray ray = sceneObject->generateRay((tX / width) , (tY / height));
				intersectionDisc = sceneObject->trace(ray);

				if (intersectionDisc.triangleID != T_RACER_TRIANGLE_NULL)
				{
					Triangle* primative = sceneObject->getTriangleByIndex(intersectionDisc.triangleID);
					lightPath.emplace_back(T_racer_Path_Vertex());
					lightPath[0].BRDFMaterialID = primative->getMaterialIndex();
					lightPath[0].hitPoint = ray.position + (ray.direction * intersectionDisc.t);
					lightPath[0].normal = primative->normal;
					lightPath[0].uv = primative->interpolatePoint(intersectionDisc);
					lightPath[0].orthnormalBasis = primative->createShadingFrame(lightPath[0].normal);
					lightPath[0].wo = ray.getincomingRayDirection();

					// Calculate the light paths. Divide result by N value for correct monte carlo estimation. 
					tracePath(ray, irradiance, lightPath);

					for (int i = 0; i < lightPath.size(); i++)
					{
						lightValue.colour = lightValue.colour + calculateDirectLighting(&lightPath[i], irradiance).colour;
					}

				}

				lightSigma.colour = lightSigma.colour + lightValue.colour;
				lightPath.clear();
			}

			lightSigma.colour = lightSigma.colour / T_RACER_SAMPLE_COUNT;
			display->setColourValue((width - 1) - tX, (height - 1) - tY, lightSigma);

			//display->setColourValue(tX, tY, lightValue);
			
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
	bool rr = (stopProbability <= T_RACER_LUMINANCE_VALUE); 

	if (rr) 
	{
		colour.colour = colour.colour * (1.0f / 1.0f - stopProbability);
	}

	return rr;
}

T_racer_Math::Colour T_racer_Renderer_PathTracer::calculateDirectLighting(T_racer_Path_Vertex* pathVertex, T_racer_Math::Colour& col)
{
	T_racer_Math::Ray  lightRay;
	T_racer_Math::Colour Ld(0.0f, 0.0f, 0.0f);
	T_racer_Path_Vertex  lightSourcePath;
	
	T_racer_Material* material = sceneObject->materials.retrieveMaterial(pathVertex->BRDFMaterialID);
	T_racer_Light_Base* lightSource = sceneObject->retrieveOneLightSource(); // Picks out a random light source to sample.
	T_racer_SampledDirection light_pos = lightSource->Sample(*pathVertex, lightRay, lightSourcePath);

	if (!sceneObject->visible(lightSourcePath.hitPoint, pathVertex->hitPoint))
	{
		return Ld;
	}

	float gTerm = geometryTerm(pathVertex, &lightSourcePath);

	T_racer_Math::Colour brdfLightValue = lightSource->Evaluate(*pathVertex);
	T_racer_Math::Colour brdfSurfaceValue = material->Evaluate(&lightRay, *pathVertex);
	Ld.colour = pathVertex->pathColour.colour * col.colour * brdfLightValue.colour  * brdfSurfaceValue.colour *  gTerm / light_pos.probabilityDensity;

	return Ld;
}


// Geometry term depends on the light source in question.
float T_racer_Renderer_PathTracer::geometryTerm(T_racer_Path_Vertex* pathVertex, T_racer_Path_Vertex *lightVertex)
{
	// TODO - Work out a better approch for working out the hitpoint for geometry term.
	// Consider using flags or related tools for differentiating light sources.
	// Consider better functions for determining probability density if needed. 
	float l;
	T_racer_Math::Vector dir = lightVertex->hitPoint - pathVertex->hitPoint;
	l = dir.normaliseSelfWithMagnitude();
	float brdfTheta = fmaxf(T_racer_Math::dot(dir, pathVertex->normal), 0.0f);
	float lightTheta = lightVertex->isPointLightSource ?  1.0 : -fmaxf(T_racer_Math::dot(dir, lightVertex->normal), 0.0f);

	return (brdfTheta * lightTheta) / l;
}
