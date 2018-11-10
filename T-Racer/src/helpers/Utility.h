/** @file Utility.h
*  @brief A collection of utilities.
*
*  Defines a collection of useful functions and classes for
*  the pathtracer. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

inline void RELEASE_RESOURCE(void*& memory) 
{
	if (memory) { delete memory; memory = nullptr; }
}

inline void T_RACER_RELEASE_BUFFER(void*& buffer) 
{
	if (buffer) { delete[] buffer; buffer = nullptr; }
}