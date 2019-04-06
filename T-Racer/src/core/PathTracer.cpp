#include "helpers/Utility.h"

#include "Display.h"
#include "PathTracer.h"

constexpr int  T_RACER_TRIANGLE_OR_INDEX_NULL = -1;
constexpr float T_RACER_LUMINANCE_VALUE = 0.1f;

// constexpr int T_RACER_SAMPLE_COUNT = 1;

constexpr int T_RACER_PATH_INITIAL_COUNT = 20;

constexpr int T_RACER_MINIMUM_BOUNCE = 4; // PBRT derived. 


// Temporary solution until the bidirectional elements are added.
#define LIGHT_TRACER_INTEGRATOR
//#define PATH_TRACER_INTEGRATOR


T_racer_Renderer_PathTracer::T_racer_Renderer_PathTracer()
{
	T_RACER_RELEASE_RESOURCE((void*&)display);
}

T_racer_Renderer_PathTracer::~T_racer_Renderer_PathTracer()
{
	if (totalRadiance)
	{
		delete totalRadiance; 
		totalRadiance = nullptr;
	}
}

void T_racer_Renderer_PathTracer::Render()
{
	sceneObject->setupScene();
#ifdef _DEBUG
	threadCount = 1;
#endif // DEBUG
	
	// Set up a pool of threads and render over multiple threads.
	if (threadCount > 0) 
	{
		totalRadiance = new T_racer_Math::Colour[(int)display->getWidth() * (int)display->getHeight()];
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
			if (display->quit) { return; }
		}

		return;
	}
}

void T_racer_Renderer_PathTracer::traceCameraPath(int tX, int tY, std::vector<T_racer_Path_Vertex>& cameraPath)
{
	T_racer_TriangleIntersection  lightSourceHit;
	T_racer_TriangleIntersection  intersectDisc;
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = true;

	// Calculate the initial ray.
	T_racer_Math::Ray  ray = sceneObject->generateRay(tX / display->getWidth(), tY / display->getHeight());
	int pathIndex = 0;

	T_racer_SampledDirection  wi;
	T_racer_Math::Colour  brdfValue;
	T_racer_Math::Colour  pathTroughput = T_racer_Math::Colour(1,1,1);
	
	intersectDisc = sceneObject->trace(ray);
	lightSourceHit = sceneObject->hitsLightSource(&ray);

	if (lightSourceHit.intersection && lightSourceHit.t < intersectDisc.t)
	{
		T_racer_Light_Base* light = sceneObject->retrieveLightByIndex(lightSourceHit.lightID);
		cameraPath.emplace_back(T_racer_Path_Vertex());
		cameraPath[0].pathColour = pathTroughput * light->getIntensity();
		cameraPath[0].hitPoint = ray.position + (ray.direction * lightSourceHit.t);
		cameraPath[0].isOnLightSource = true;
		cameraPath[0].lightSourceId = lightSourceHit.lightID;
		cameraPath[0].normal = light->getLightSurfaceNormal(lightSourceHit.lightTriangleID);
		cameraPath[0].wo = ray.getincomingRayDirection();
	}
	else if (intersectDisc.triangleID != T_RACER_TRIANGLE_OR_INDEX_NULL)
	{
		Triangle* primative = sceneObject->getTriangleByIndex(intersectDisc.triangleID);
		cameraPath.emplace_back(T_racer_Path_Vertex());
		cameraPath[0].BRDFMaterialID = primative->getMaterialIndex();
		cameraPath[0].hitPoint = ray.position + (ray.direction * intersectDisc.t);
		cameraPath[0].normal = primative->normal;
		cameraPath[0].uv = primative->interpolatePoint(intersectDisc);
		cameraPath[0].orthnormalBasis = primative->createShadingFrame(cameraPath[0].normal);
		cameraPath[0].wo = ray.getincomingRayDirection();
		cameraPath[0].pathColour = pathTroughput;
		cameraPath[0].lightSourceId = cameraPath[0].lightSourceId;
		terminatePath = false;
	}

	while (!terminatePath)
	{
		surfaceMaterial = sceneObject->materials.retrieveMaterial(cameraPath[pathIndex].BRDFMaterialID);

		// new brdf approch.
		brdfValue = surfaceMaterial->SampleMaterial(sampler, wi, cameraPath[pathIndex]);
		ray = T_racer_Math::Ray(cameraPath[pathIndex].hitPoint, wi.direction);

		pathTroughput = pathTroughput * brdfValue;
		pathTroughput = pathTroughput * fabsf(T_racer_Math::dot(wi.direction, cameraPath[pathIndex].normal));
		pathTroughput = pathTroughput / wi.probabilityDensity;

		if (wi.probabilityDensity == 0.0f) { terminatePath = true; }

		cameraPath[pathIndex].pathColour = pathTroughput;

		terminatePath = (pathTroughput.colour.X == 0.0f && pathTroughput.colour.Y == 0.0f && pathTroughput.colour.Z == 0.0f);

		if (pathIndex > T_RACER_MINIMUM_BOUNCE)
		{
			terminatePath = !RussianRoulette(pathTroughput, &cameraPath[pathIndex]);
		}
		if (pathIndex > 100)
		{
			terminatePath = true;
		}

		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
		if (!terminatePath)
		{
			intersectDisc = sceneObject->trace(ray);
			lightSourceHit = sceneObject->hitsLightSource(&ray);

			if (lightSourceHit.intersection && lightSourceHit.t < intersectDisc.t)
			{
				T_racer_Light_Base* light = sceneObject->retrieveLightByIndex(lightSourceHit.lightID);
				terminatePath = true;
				pathIndex++;
				cameraPath.emplace_back(T_racer_Path_Vertex());
				cameraPath[pathIndex].pathColour = pathTroughput * light->getIntensity();
				cameraPath[pathIndex].hitPoint = cameraPath[pathIndex - 1].hitPoint + (wi.direction * lightSourceHit.t);
				cameraPath[pathIndex].isOnLightSource = true;
				cameraPath[pathIndex].lightSourceId = lightSourceHit.lightID;
				cameraPath[pathIndex].normal = light->getLightSurfaceNormal(lightSourceHit.lightTriangleID);
			}
			else if (intersectDisc.triangleID != T_RACER_TRIANGLE_OR_INDEX_NULL)
			{
				// Create a new light path.
				pathIndex++;

				// Add to the light index.
				Triangle* primative = sceneObject->getTriangleByIndex(intersectDisc.triangleID);
				cameraPath.emplace_back(T_racer_Path_Vertex());
				cameraPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
				cameraPath[pathIndex].hitPoint = cameraPath[pathIndex - 1].hitPoint + (wi.direction * intersectDisc.t);
				cameraPath[pathIndex].wo = -wi.direction;
				cameraPath[pathIndex].normal = primative->normal;
				cameraPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
				cameraPath[pathIndex].orthnormalBasis = primative->createShadingFrame(cameraPath[pathIndex].normal);
				cameraPath[pathIndex].pathColour = pathTroughput;
			}
			else
			{
				terminatePath = true;
			}
		}
	}
}

void T_racer_Renderer_PathTracer::traceLightPath(std::vector<T_racer_Path_Vertex>& LightPath)
{
	T_racer_TriangleIntersection  lightSourceHit;
	T_racer_TriangleIntersection  intersectDisc;
	T_racer_Material*  surfaceMaterial = nullptr;
	bool terminatePath = true;

	// Calculate the initial ray.
	T_racer_Math::Ray  ray;
	int pathIndex = 1;

	T_racer_SampledDirection  wi;
	T_racer_Math::Colour  brdfValue;
	T_racer_Math::Colour  pathTroughput = T_racer_Math::Colour(1, 1, 1);

	int lightIndex;
	T_racer_Light_Base* lightSource = sceneObject->retrieveOneLightSource(&sampler, lightIndex);
	float pdfLight = sceneObject->getProbabilityDensityLightSourceSelection();
	LightPath.emplace_back(lightSource->SamplePoint(pdfLight));
	LightPath[0].lightSourceId = lightIndex;
	pathTroughput = (pathTroughput) / pdfLight;
	LightPath[0].pathColour = pathTroughput * lightSource->getIntensity();
	wi = sceneObject->retrieveLightByIndex(LightPath[0].lightSourceId)->SampleDirection(&sampler, &LightPath[0]);
	pathTroughput = pathTroughput * T_racer_Math::dot(LightPath[0].normal, wi.direction) / wi.probabilityDensity;
	
	ray = T_racer_Math::Ray(LightPath[0].hitPoint, wi.direction);

	intersectDisc = sceneObject->trace(ray);
	lightSourceHit = sceneObject->hitsLightSource(&ray);

	if (intersectDisc.triangleID != T_RACER_TRIANGLE_OR_INDEX_NULL)
	{
		Triangle* primative = sceneObject->getTriangleByIndex(intersectDisc.triangleID);
		LightPath.emplace_back(T_racer_Path_Vertex());
		LightPath[1].BRDFMaterialID = primative->getMaterialIndex();
		LightPath[1].hitPoint = ray.position + (ray.direction * intersectDisc.t);
		LightPath[1].normal = primative->normal;
		LightPath[1].uv = primative->interpolatePoint(intersectDisc);
		LightPath[1].orthnormalBasis = primative->createShadingFrame(LightPath[1].normal);
		LightPath[1].wo = ray.getincomingRayDirection();
//		LightPath[1].pathColour = pathTroughput * lightSource->getIntensity();
		LightPath[1].lightSourceId = LightPath[0].lightSourceId;
		terminatePath = false;
	}

	while (!terminatePath)
	{
		surfaceMaterial = sceneObject->materials.retrieveMaterial(LightPath[pathIndex].BRDFMaterialID);

		// new brdf approch.
		brdfValue = surfaceMaterial->SampleMaterial(sampler, wi, LightPath[pathIndex]);
		ray = T_racer_Math::Ray(LightPath[pathIndex].hitPoint, wi.direction);

		pathTroughput = pathTroughput * brdfValue;
		pathTroughput = pathTroughput * fabsf(T_racer_Math::dot(wi.direction, LightPath[pathIndex].normal));
		pathTroughput = pathTroughput / wi.probabilityDensity;

		if (wi.probabilityDensity == 0.0f) { terminatePath = true; }

		LightPath[pathIndex].pathColour = pathTroughput * lightSource->getIntensity();

		terminatePath = (pathTroughput.colour.X == 0.0f && pathTroughput.colour.Y == 0.0f && pathTroughput.colour.Z == 0.0f);

		if (pathIndex > T_RACER_MINIMUM_BOUNCE)
		{
			terminatePath = !RussianRoulette(pathTroughput, &LightPath[pathIndex]);
		}
		if (pathIndex > 3)
		{
			terminatePath = true;
		}

		// else trace the scene again.
		// If we hit a light source also terminate the path.
		// then loop.
		if (!terminatePath)
		{
			intersectDisc = sceneObject->trace(ray);
			lightSourceHit = sceneObject->hitsLightSource(&ray);

			if (lightSourceHit.intersection && lightSourceHit.t < intersectDisc.t)
			{
				terminatePath = true;
			}
			else if (intersectDisc.triangleID != T_RACER_TRIANGLE_OR_INDEX_NULL)
			{
				// Create a new light path.
				pathIndex++;

				// Add to the light index.
				Triangle* primative = sceneObject->getTriangleByIndex(intersectDisc.triangleID);
				LightPath.emplace_back(T_racer_Path_Vertex());
				LightPath[pathIndex].BRDFMaterialID = primative->getMaterialIndex();
				LightPath[pathIndex].hitPoint = LightPath[pathIndex - 1].hitPoint + (wi.direction * intersectDisc.t);
				LightPath[pathIndex].wo = -wi.direction;
				LightPath[pathIndex].normal = primative->normal;
				LightPath[pathIndex].uv = primative->interpolatePoint(intersectDisc);
				LightPath[pathIndex].orthnormalBasis = primative->createShadingFrame(LightPath[pathIndex].normal);
				//LightPath[pathIndex].pathColour = pathTroughput * lightSource->getIntensity();
				LightPath[pathIndex].lightSourceId = LightPath[0].lightSourceId;
			}
			else
			{
				terminatePath = true;
			}
		}
	}
}

void T_racer_Renderer_PathTracer::renderThreaded()
{
	// Data types for rendering threaded.
	T_racer_TriangleIntersection intersectionDisc;
	T_racer_TriangleIntersection lightSourceHit;

	T_racer_Math::Vector bias;

	T_racer_Math::Colour irradiance;
	T_racer_Math::Colour lightValue;

	T_racer_Math::Ray ray;

	std::vector<T_racer_Path_Vertex>  cameraPath;
	std::vector<T_racer_Path_Vertex>  lightPath;
	cameraPath.reserve(T_RACER_PATH_INITIAL_COUNT);
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
			irradiance = T_racer_Math::Colour(1.0f, 1.0f, 1.0f);
			lightValue = T_racer_Math::Colour(0.0f, 0.0f, 0.0f);

			traceCameraPath(tX, tY, cameraPath);
			traceLightPath(lightPath);

#ifdef PATH_TRACER_INTEGRATOR
			for (int i = 0; i < cameraPath.size(); i++)
			{
				if (cameraPath[i].isOnLightSource )
				{
					if (cameraPath[i - 1].isFresnelSurface == true) 
					{
						// Do something diffrent.
						lightValue.colour += cameraPath[i].pathColour.colour;
					}
					else if(cameraPath.size() == 1)
					{
						lightValue.colour += T_racer_Math::Colour(1, 1, 1).colour;
					}

				}
				else
				{
					lightValue.colour = lightValue.colour + calculateDirectLighting(&cameraPath[i]).colour;
				}
			}
			totalRadiance[tX + ((int)tWidth * tY)].colour = totalRadiance[tX + ((int)tWidth * tY)].colour + lightValue.colour;
			display->setColourValue(tX, (height - 1) - tY, totalRadiance[tX + ((int)tWidth * tY)] / sampleCount);
#elif defined LIGHT_TRACER_INTEGRATOR
			for (int i = 0; i < lightPath.size(); i++)
			{
				int imagePlaneIndex = sceneObject->mainCamera->pixelPointOnCamera(lightPath[i].hitPoint);
				//std::cout << "imagePlaneIndex value: " << imagePlaneIndex << "\n";
				if (imagePlaneIndex != T_RACER_TRIANGLE_OR_INDEX_NULL)
				{
					totalRadiance[imagePlaneIndex].colour += directLightingLightTracer(&lightPath[i]).colour;
				}
			}
#endif
			
			if (display->quit) { return; }
			lightPath.clear();
			cameraPath.clear();
		}

		compleatedTiles++;

		if (compleatedTiles == tileCount) 
		{
			std::cout << "Sample Count - " << sampleCount << std::endl;
			compleatedTiles = 0;
			currentTile = 0;

#ifdef LIGHT_TRACER_INTEGRATOR
			
			for (int y = 0; y < display->getHeight(); y++)
			{
				for (int x = 0; x < display->getWidth(); x++)
				{
					display->setColourValue(x, (height - 1) - y, totalRadiance[x + ((int)tWidth * y)] / sampleCount);
				}
			}

#endif // LIGHT_TRACER_INTEGRATOR

			sampleCount++;
		}
	}

	return;
}

// Weight the value according to the luminance if the luminance is less than a random value.
bool T_racer_Renderer_PathTracer::RussianRoulette(T_racer_Math::Colour& colour, T_racer_Path_Vertex* pathIndex)
{
	T_racer_Math::Sampler   sampler;
	float stopProbability = sampler.Random();
	bool rr = (stopProbability < colour.getLuminance()); 

	if (rr) 
	{
		colour.colour = colour.colour * (1.0f / colour.getLuminance());
	}

	return rr;
}

T_racer_Math::Colour T_racer_Renderer_PathTracer::calculateDirectLighting(T_racer_Path_Vertex* pathVertex)
{
	T_racer_Math::Colour Ld(0.0f, 0.0f, 0.0f);
	if (pathVertex->isFresnelSurface) 
	{
		return Ld;
	}

	T_racer_Math::Ray  lightRay;
	T_racer_Path_Vertex  lightSourcePath;
	T_racer_Material* material = sceneObject->materials.retrieveMaterial(pathVertex->BRDFMaterialID);
	T_racer_Light_Base* lightSource = sceneObject->retrieveOneLightSource(&sampler); // Picks out a random light source to sample.
	T_racer_SampledDirection light_pos = lightSource->Sample(*pathVertex, lightRay, lightSourcePath);

	if (!sceneObject->visible(lightSourcePath.hitPoint, pathVertex->hitPoint))
	{
		return Ld;
	}

	float gTerm = geometryTerm(pathVertex, &lightSourcePath);
	T_racer_Math::Colour lightValue = lightSource->Evaluate(*pathVertex);
	T_racer_Math::Colour brdfSurfaceValue = material->Evaluate(&lightRay, *pathVertex);
	Ld.colour = pathVertex->pathColour.colour * lightValue.colour  * brdfSurfaceValue.colour *  gTerm / light_pos.probabilityDensity;

	return Ld;
}


// Geometry term depends on the light source in question.
float T_racer_Renderer_PathTracer::geometryTerm(T_racer_Path_Vertex* pathVertex, T_racer_Path_Vertex *lightVertex)
{
	// TODO - Work out a better approch for working out the hitpoint for geometry term.
	// Consider using flags or related tools for differentiating light sources.
	// Consider better functions for determining probability density if needed. 
	float lsq;
	T_racer_Math::Vector dir = lightVertex->hitPoint - pathVertex->hitPoint;
	lsq = dir.normaliseSelfWithMagnitudeSq();
	float brdfTheta = fmaxf(T_racer_Math::dot(dir, pathVertex->normal), 0.0f);
	float lightTheta = lightVertex->isPointLightSource ?  1.0 : fmaxf(T_racer_Math::dot(-dir, lightVertex->normal), 0.0f);
	return (brdfTheta * lightTheta) / lsq;
}

float T_racer_Renderer_PathTracer::cameraTerm(T_racer_Path_Vertex * pathVertex, T_racer_Math::Vector& camDir)
{
	float lsq = camDir.normaliseSelfWithMagnitudeSq();

	float w = fabsf(T_racer_Math::dot(pathVertex->normal, camDir)) / lsq;
	w *= sceneObject->mainCamera->cameraImportance(camDir);

	return w;
}

T_racer_Math::Colour T_racer_Renderer_PathTracer::directLightingLightTracer(T_racer_Path_Vertex* pathVertex)
{
	// Need a refrence to the light source. 
	T_racer_Math::Colour Ld(0.0f, 0.0f, 0.0f);
	if (pathVertex->isFresnelSurface || !sceneObject->visible(pathVertex->hitPoint, sceneObject->mainCamera->getPosition()))
	{
		return Ld;
	}
	
	T_racer_Math::Vector cameraConnection = pathVertex->hitPoint - sceneObject->mainCamera->getPosition();
	float gTermCamera = cameraTerm(pathVertex, cameraConnection);

	if (gTermCamera < 0) 
	{
		return Ld; 
	}

	T_racer_Light_Base* light = sceneObject->retrieveLightByIndex(pathVertex->lightSourceId);

	if (pathVertex->isOnLightSource) 
	{
		Ld = pathVertex->pathColour * fabsf(T_racer_Math::dot(pathVertex->normal, cameraConnection)) * gTermCamera; 
	}
	else 
	{
		// not a light source. We need to know the light we are going to trace from.
		T_racer_Material* surfaceMaterial = sceneObject->materials.retrieveMaterial(pathVertex->BRDFMaterialID);
		T_racer_SampledDirection wi;
		T_racer_Math::Colour brdfValue = surfaceMaterial->Evaluate2(wi, *pathVertex);

		Ld = pathVertex->pathColour * brdfValue * fabsf(T_racer_Math::dot(pathVertex->normal, cameraConnection)) * gTermCamera;
	}

	return Ld;
}
