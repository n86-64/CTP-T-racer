/** @file SampledObjects.h
*  @brief A set of sampled objects.
*
*  A collecion of objects for use in various ampling scanarios.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

// The direction the ray should travel along with the probibility density.
struct T_racer_SampledDirection
{
	T_racer_Math::Vector point;
	T_racer_Math::Vector direction;
	float				 probabilityDensity;

	// pdf values for area lights.
	float				 probabilityDensityArea;
};
