/** @file PathVertex.h
*  @brief Information on path collision points.
*
*  Defines a point where intersection between
*  a path and a surface occurs.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "helpers/Math_Colour.h"
#include "helpers/Math_Vector.h"
#include "helpers/Math_Matrix.h"

struct T_racer_Path_Vertex
{
	// Additional ray properties
	T_racer_Math::Vector	uv;
	T_racer_Math::Vector	normal;
	T_racer_Math::Matrix3X3 orthnormalBasis;
	T_racer_Math::Vector	hitPoint;
	T_racer_Math::Vector    wo; // incoming ray direction. 
	T_racer_Math::Colour    pathColour;
	unsigned int			BRDFMaterialID = 0;
};