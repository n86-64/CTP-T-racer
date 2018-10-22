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

	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(float x);
		Vector3(float x, float y);
		Vector3(float x, float y, float z);
		Vector3(const Vector3&  vector);

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
		Vector3			 operator+(Vector3 vec);
		void			 operator+=(Vector3 vec);
		Vector3			 operator-(Vector3 vec);
		void		     operator-=(Vector3 vec);

		// element based multiplication/division.
		Vector3			 operator*(Vector3 vec);
		void			 operator*=(Vector3 vec);
		Vector3			 operator/(Vector3 vec);
		void			 operator/=(Vector3 vec);

		// Scalier Operations
		Vector3			 operator*(float scalier);
		Vector3			 operator*(int scalier);
		void			 operator*=(float scalier);
		void			 operator*=(int scalier);

		// Other Vector Operations
		Vector3	normalise();
		void normaliseSelf();

		// Returns the magnitude used to normalise this vector. 
		float normaliseSelfWithMagnitude();

		// Uitlity functions.
		float Magnitude();


	private:
		union 
		{
			float values[3] = { 0.0f, 0.0f, 0.0f };
		};
	};

	
	inline float dot(Vector3 a, Vector3 b) 
	{
		return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
	}

	inline Vector3 cross(Vector3 a, Vector3 b) 
	{
		return Vector3(
			(a.y() * b.z()) - (a.z() * b.y()),
			(a.z() * b.x()) - (a.x() * b.z()),
			(a.x() * b.y()) - (a.y() * b.x())
		);
	}
}