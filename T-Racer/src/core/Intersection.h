/** @file Intersection.h
*  @brief A collection of data structures for intersection.
*
*  Defines a collection of intersection resolutions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once


#include "helpers/Math_Vector.h"

struct T_racer_TriangleIntersection 
{
	bool intersection = false;

	// w, u, v are berycentic coordinates.
	// t is the length of the ray. Used to derive P (point of intersection.)
	float u = 0.0f, v = 0.0f, t = 0.0f;
	float w = 0.0f;

	void setW() { w = 1 - u - v; }
};