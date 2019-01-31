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

// The russian roulette constant.
constexpr int T_RACER_SAMPLER_RR_CONSTANT = 0.1f;

class T_racer_Renderer_PathTracer : public T_racer_Renderer_Base  
{
public:
	T_racer_Renderer_PathTracer();

	virtual void renderThreaded() override;
	virtual void Render() override;

protected:
	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance) override;
	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance, std::vector<T_racer_Path_Vertex>& lightPath) override;

private:
	// Performs RussianRoulette on the path and then returns the 
	bool RussianRoulette(T_racer_Math::Colour& colour, T_racer_Path_Vertex* pathIndex);
	T_racer_Math::Colour calculateDirectLighting(T_racer_Path_Vertex* pathIndex, T_racer_Math::Colour& col);
	bool isLightVisible(T_racer_Light_Base* lightSource, T_racer_Path_Vertex* pathVertex);
	float geometryTerm(T_racer_Path_Vertex* pathVertex, T_racer_Path_Vertex *lightVertex);
};