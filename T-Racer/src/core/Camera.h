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

#include "Transform.h"

class Camera 
{
public:
	Camera();

	T_racer_CameraTransform  getCameraTransform();
	

private:
	float fovX, fovY;
	float resX, resY;

	T_racer_Math::Vector3    position;
};