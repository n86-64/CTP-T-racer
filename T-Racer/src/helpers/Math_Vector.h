/** @file Math_Vector.h
*  @brief A n-dimenstional column vector.
*
*  This defines a vector along with a set of operations.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

class T_racer_Vector3 
{
public:
	T_racer_Vector3();

	float x();
	float y();
	float z();
	float w();

	// Operators.
	T_racer_Vector3 operator+(T_racer_Vector3& vec);
	T_racer_Vector3& operator+=(T_racer_Vector3& vec);
	T_racer_Vector3 operator-(T_racer_Vector3& vec);
	T_racer_Vector3 operator-=(T_racer_Vector3& vec);

	T_racer_Vector3 operator-=(T_racer_Vector3& vec);
private:
	float values[3] = { 0.0f, 0.0f, 0.0f};
	float magnitude; // Recalculated when a value is changed. Easy and simple.

private: 	// Uitlity functions.
	float calcualteMagnitude(); 
};
