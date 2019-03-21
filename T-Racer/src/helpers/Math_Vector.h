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

#include <cmath>

#include "assimp/vector2.h"
#include "assimp/vector3.h"

#include "helpers/Math_Error.h"

// A set of vector operations that can be called at any time. 
namespace T_racer_Math
{
	// TODO - Add inter-vector operations here. 

	class Vector
	{
	public:
		Vector() = default;
		Vector(float x);
		Vector(float x, float y);
		Vector(float x, float y, float z);
		Vector(float x, float y, float z, float w);
		Vector(const Vector&  vector);
		Vector(aiVector2D vector) { values[0] = vector.x; values[1] = vector.y; };
		Vector(aiVector3D vector) { values[0] = vector.x; values[1] = vector.y; values[2] = vector.z; };

		// get/set components.
		float x() { return values[0]; };
		float y() { return values[1]; };
		float z() { return values[2]; };

		void x(float value) { values[0] = value; };
		void y(float value) { values[1] = value; };
		void z(float value) { values[2] = value; };

		float maxComp();
		float minComp();

		// May be needed.
		float*	getVectorAsArray();

		// Linear operations
		Vector			 operator+(Vector vec);
		void			 operator+=(Vector vec);
		Vector			 operator-(Vector vec);
		Vector			 operator-();
		void		     operator-=(Vector vec);

		// element based multiplication/division.
		Vector			 operator*(Vector vec);
		void			 operator*=(Vector vec);
		Vector			 operator/(Vector vec);
		void			 operator/=(Vector vec);
		Vector			 operator/(int scalier);
		Vector			 operator/(float scalier);

		// Scalier Operations
		Vector			 operator*(float scalier);
		Vector			 operator*(int scalier);
		void			 operator*=(float scalier);
		void			 operator*=(int scalier);

		Vector			 inverse(float scailer);

		// Other Vector Operations
		Vector	normalise();
		void normaliseSelf();

		// Returns the magnitude used to normalise this vector. 
		float normaliseSelfWithMagnitude();

		float normaliseSelfWithMagnitudeSq();

		// Uitlity functions.
		float Magnitude();
		float MagnitudeSq();


	public:
		union 
		{
			float values[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			struct 
			{
				float X;
				float Y;
				float Z;
				float W;
			};
		};
	};

	inline Vector min(Vector& a, Vector& b) 
	{
		return Vector(fminf(a.X, b.X), fminf(a.Y, b.Y), fminf(a.Z, b.Z));
	}

	inline Vector max(Vector& a, Vector& b)
	{
		return Vector(fmaxf(a.X, b.X), fmaxf(a.Y, b.Y), fmaxf(a.Z, b.Z));
	}
	
	inline float dot(Vector a, Vector b) 
	{
		return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
	}

	inline Vector cross(Vector a, Vector b) 
	{
		return Vector(
			(a.Y * b.Z) - (a.Z * b.Y),
			(a.Z * b.X) - (a.X * b.Z),
			(a.X * b.Y) - (a.Y * b.X)
		);
	}

	inline float firstPositiveInVec(Vector& v1, Vector& v2) 
	{
		Vector v11(fabsf(v1.X), fabsf(v1.Y), fabsf(v1.Z));

		if (v11.X > v11.Y && v11.X > v11.Z) 
		{
			return (v2.X + T_RACER_EPSILON);
		}
		else if (v11.Y > v11.X && v11.Y > v11.Z) 
		{
			return (v2.Y + T_RACER_EPSILON);
		}

		return (v2.Z + T_RACER_EPSILON);
	}

	// A series of vector constants.
	const Vector up(0.0f, 1.0f, 0.0f);
	const Vector right(1.0f, 0.0f, 0.0f);
	const Vector forward(0.0f, 0.0f, 1.0f);
}