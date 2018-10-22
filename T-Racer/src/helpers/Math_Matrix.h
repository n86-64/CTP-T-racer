/** @file Math_Matrix.h
*  @brief A definition of a set of mataracies
*
*  Defines a grid maxtrix up to 4-dimenstions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once


namespace T_racer_Math 
{
	class Matrix4X4 
	{
	public:
		Matrix4X4();

	private:
		// Initialy set to be an identity matrix.
		float matrix[16] = 
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	};
}