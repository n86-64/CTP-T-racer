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
	T_racer_Renderer_PathTracer() = default;

	virtual void Render() override;

protected:
	virtual void tracePath() override;

private:
	std::vector<T_racer_Path_Vertex>   lightPath;

	// returns the index of a triangle that was hit by the path-tracer.
	int sortTriangles(T_racer_BVH_CollisionQueue_t& collisions, T_racer_TriangleIntersection& intersection);

};