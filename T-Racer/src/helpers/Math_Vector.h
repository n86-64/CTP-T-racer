/** @file Math_Vector.h
*  @brief A n-dimenstional column vector.
*
*  This defines a vector along with a set of operations for said vectors.
*  Can be used to represent both colour and data.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

// A set of vector operations that can be called at any time. 
namespace T_racer_Math 
{
	// TODO - Add inter-vector operations here. 

}

class T_racer_Vector3 
{
public:
	T_racer_Vector3() = default;
	T_racer_Vector3(float x);
	T_racer_Vector3(float x, float y);
	T_racer_Vector3(float x, float y, float z);
	T_racer_Vector3(const T_racer_Vector3&  vector);

	// get/set components.
	float x() { return values[0]; };
	float y() { return values[1]; };
	float z() { return values[2]; };

	void x(float value) { values[0] = value; };
	void y(float value) { values[1] = value; };
	void z(float value) { values[2] = value; };

	// May be needed.
	float*	getVectorAsArray();

	// Linear operations
	T_racer_Vector3 operator+(T_racer_Vector3 vec);
	void			operator+=(T_racer_Vector3 vec);
	T_racer_Vector3 operator-(T_racer_Vector3 vec);
	void		    operator-=(T_racer_Vector3 vec);

	// row based multiplication.
	T_racer_Vector3  operator*(T_racer_Vector3 vec);
	void			 operator*=(T_racer_Vector3 vec);
	
	T_racer_Vector3  operator*(float scalier);
	T_racer_Vector3  operator*(int scalier);
	void			 operator*=(float scalier);
	void			 operator*=(int scalier);

	// Other Vector Operations
	T_racer_Vector3	normalise();

private:
	float values[3] = { 0.0f, 0.0f, 0.0f };


private: 	
	// Uitlity functions.
	float calcualteMagnitude(); 
};
