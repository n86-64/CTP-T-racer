/** @file Renderers.h
*  @brief A path-tracer renderer.
*
*  Defines a path-tracing renderer.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "PathVertex.h"
#include "Renderers.h"

class T_racer_Renderer_PathTracer : public T_racer_Renderer_Base  
{
public:
	T_racer_Renderer_PathTracer();
	~T_racer_Renderer_PathTracer();

	virtual void renderThreaded() override;
	virtual void Render() override;

	virtual void postDisplayUpdate() override { while (!display->quit) { display->update(); } }

protected:
	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath, int startingPath) override;
	void tracePathLight(T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath);

private:
	bool RussianRoulette(T_racer_Math::Colour& colour, T_racer_Path_Vertex* pathIndex);
	T_racer_Math::Colour calculateDirectLighting(T_racer_Path_Vertex* pathIndex);
	float geometryTerm(T_racer_Path_Vertex* pathVertex, T_racer_Path_Vertex *lightVertex);
	
	// light tracer functions.
	float cameraTerm(T_racer_Path_Vertex* pathVertex);
	T_racer_Math::Colour directLightingLightTracer(T_racer_Path_Vertex* pathVertex);

private:
	T_racer_Math::Colour*  totalRadiance = nullptr;
};