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


	virtual T_racer_Math::Colour Evaluate(T_racer_Path_Vertex& pathVertex) = 0;
	virtual T_racer_SampledDirection Sample(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay, T_racer_Path_Vertex& lightSourceVertex) = 0;
	virtual float probabilityDensity(T_racer_Path_Vertex& pathVertex, T_racer_Math::Ray& inputRay) = 0;

	// Determines the cosine value for the light source.
	virtual float surfaceCosine(T_racer_Path_Vertex& vertex) = 0;

	T_racer_Math::Vector getPosition() const { return position; }
	T_racer_Math::Vector getRotation() const { return rotation; }

	void				 setPosition(T_racer_Math::Vector newPos) { position = newPos; }

protected:
	T_racer_Math::Colour	intensity = T_racer_Math::Colour(10.0f, 10.0f, 10.0f);

	// TODO - Add any additional required variables here. 
	T_racer_Math::Vector    position;
	T_racer_Math::Vector	rotation;
};