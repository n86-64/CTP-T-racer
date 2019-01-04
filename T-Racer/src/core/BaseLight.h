/** @file BaseLight.h
*  @brief A basic class for lights.
*
*  A basic class for use by various lights.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "PathVertex.h"
#include "SampledObjects.h"

#include "helpers/Math_Ray.h"
#include "helpers/Math_Colour.h"


class T_racer_Light_Base 
{
public:
	T_racer_Light_Base() = default;

	virtual T_racer_Math::Colour Sample(T_racer_SampledDirection sampledDirection) = 0;
	virtual T_racer_Math::Colour Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay) = 0;
	virtual float probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay) = 0;

protected:
	// TODO - Add any additional required variables here. 
	T_racer_Math::Vector    position;
	T_racer_Math::Vector	rotation;
};