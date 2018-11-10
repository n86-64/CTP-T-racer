/** @file Vertex.h
*  @brief A vertex definition.
*
*  Stores information per-vertex for models and other 
*  3D objects.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include "helpers/FileReader.h"
#include "helpers/Math_Vector.h"

struct T_racer_Vertex 
{
	T_racer_Math::Vector3		position;
	T_racer_Math::Vector3		normal;
	T_racer_Math::Vector3		texCoord;

	T_racer_Vertex() = default;
	T_racer_Vertex(T_racer_Buffer buffer) 
	{
		std::string  data;
		buffer.extractData(data, 0, buffer.getBufferSize());

		// Parse data.
		
	}
};