/** @file Camera.h
*  @brief A ray-tracing camera.
*
*  Defines a basic pinhole camera model. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "helpers/Math_Matrix.h"
#include "helpers/Math_Vector.h"
#include "helpers/Math_Trig.h"


#include "Transform.h"

class T_racer_Camera 
{
public:
	T_racer_Camera() = default;

	// Creates a view and perspective matrix for the corrisponding camera. 
	T_racer_CameraTransform  getCameraTransform();

	float getFoV() const { return fov; }
	float getWidth() const { return resX; }
	float getHeight() const { return resY; }

	float getNearZ() const { return near; }
	float getFarZ() const { return far; }

	void setResolution(float x, float y) { resX = x; resY = y; }
	float getAspectRatio() const { return resX / resY; }

	T_racer_Math::Vector  getPosition() const { return position; }
	T_racer_Math::Vector  getForward() { return position + target; }

private:
	float fov = radians(90.0f); // fov on the y-axis.
	float resX, resY;
	float near = 0.1f, far = 100.0f;

	T_racer_Math::Vector    position = T_racer_Math::Vector(0.0f, 0.0f, -2.0f);
	T_racer_Math::Vector    target = T_racer_Math::forward;
};