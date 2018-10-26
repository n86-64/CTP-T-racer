/** @file Triangle.h
*  @brief Triangle Object.
*
*  Defines a triangle primitive along with triangle operators.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include "core/Vertex.h"

constexpr int VERTEX_COUNT = 3;

class Triangle 
{
public:
	Triangle();

private:
	T_racer_Vertex   verticies[VERTEX_COUNT] = { 0 };
	unsigned int materialID = 0;
};