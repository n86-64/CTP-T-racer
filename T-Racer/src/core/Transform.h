/** @file Transform.h
*  @brief A basic 3D transform.
*
*  Basic transform object.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "helpers/Math_Matrix.h"

struct T_racer_CameraTransform 
{
	T_racer_Math::Matrix4X4  view;
	T_racer_Math::Matrix4X4  projection;
};