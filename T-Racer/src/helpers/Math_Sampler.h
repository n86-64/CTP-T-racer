/** @file Sampler.h
*  @brief A basic 1D, 2D and 3D sampler.
*
*  An object which uses RNG to generate sets of random numbers.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <random>
#include <time.h>

#include "Math_Vector.h"

namespace T_racer_Math 
{
	class Sampler 
	{
	public:
		Sampler();

		// Genrates a random number
		float Random();

		// Generates Two random Numbers
		T_racer_Math::Vector Random2();

		// Generates three random numbers.
		T_racer_Math::Vector Random3();

		// Genrates a random number
		int RandomRange(int min, int max);

	private:
		// The RNG devices.
		std::random_device  rngEngine;
		std::mt19937    mersenneTwist;
		std::uniform_real_distribution<float>   data;
		std::uniform_int_distribution<int>		intData;
	};
};