/** @file Intersection.h
*  @brief A collection of data structures for intersection.
*
*  Defines a collection of intersection resolutions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once


struct T_racer_TriangleIntersection 
{
	bool intersection = false;
	float u = 0.0f, v = 0.0f, w = 0.0f;
};