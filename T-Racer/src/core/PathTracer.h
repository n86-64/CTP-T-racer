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
	T_racer_Renderer_PathTracer() = default;


	virtual void Render() override;

protected:
	virtual void tracePath(T_racer_Math::Ray initialRay, T_racer_Math::Colour& irradiance) override;


private:
	std::vector<T_racer_Path_Vertex>   lightPath;

	// returns the index of a triangle that was hit by the path-tracer.
	int sortTriangles(T_racer_BVH_CollisionQueue_t& collisions, T_racer_TriangleIntersection& intersection);

	// Performs RussianRoulette on the path and then returns the 
	bool RussianRoulette(T_racer_Math::Colour& colour, int pathIndex);

	T_racer_Math::Colour calculateDirectLighting(int pathVertex, T_racer_Math::Colour& col);

	bool isLightVisible(T_racer_Light_Base* lightSource, int pathVertex);

	float geometryTerm(T_racer_SampledDirection& wi, int pathVertex, T_racer_Light_Base* lightSource);
};