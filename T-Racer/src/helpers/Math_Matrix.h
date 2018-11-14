/** @file Math_Matrix.h
*  @brief A definition of a set of mataracies
*
*  Defines a grid maxtrix up to 4-dimenstions.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

constexpr int MATRIX_ELEMENTS_COUNT_4X4 = 16;

#include <math.h>
#include "Math_Vector.h"

namespace T_racer_Math 
{
	class Matrix4X4 
	{
	public:
		Matrix4X4() = default;
		Matrix4X4(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12,  float m13,
				  float m20, float m21, float m22, float m23,
				  float m30, float m31, float m32, float m33 )
		{
			matrix[0] = m00;
			matrix[1] = m01;
			matrix[2] = m02;
			matrix[3] = m03;
			matrix[4] = m10;
			matrix[5] = m11;
			matrix[6] = m12;
			matrix[7] = m13;
			matrix[8] = m20;
			matrix[9] = m21;
			matrix[10] = m22;
			matrix[11] = m23;
			matrix[12] = m30;
			matrix[13] = m31;
			matrix[14] = m32;
			matrix[15] = m33;
		};

		// Return a value from the matrix.
		float value(int row, int column) 
		{
			return m[row][column]; 
		}

		// matrix operations
		Vector    operator* (Vector mat);
		Matrix4X4 operator*(Matrix4X4 matrix);


	private:

		union 
		{
			// Initialy set to be an identity matrix.
			float matrix[MATRIX_ELEMENTS_COUNT_4X4] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			float m[4][4]; 
		};
	};

	inline float getMatrixDeterminant(Matrix4X4 mat) 
	{
		float d1 = mat.value(0, 0) + mat.value(1, 1) + mat.value(2, 2) + mat.value(3, 3);
		float d2 = mat.value(3, 0) + mat.value(2, 1) + mat.value(1, 2) + mat.value(0, 3);

		return ((d1 - d2));
	}


	// Returns the input matrix if the operation fails.
	inline Matrix4X4 getInverseMatrix(Matrix4X4 mat) 
	{
		float d = getMatrixDeterminant(mat);
		if (d == 0) 
		{
			return Matrix4X4();
		}

		return Matrix4X4
		(
			1 / mat.value(0, 0), mat.value(0, 1), mat.value(0, 2), mat.value(0, 3),
			mat.value(1, 0), 1 / mat.value(1, 1), mat.value(1, 2), mat.value(1, 3),
			mat.value(2, 0), mat.value(2, 1), mat.value(2, 2), mat.value(2, 3),
		     mat.value(3, 0), mat.value(3, 1), mat.value(3, 2), 1 / mat.value(3, 3)
		);
	}


	// Generates a translation matrix. 
	inline Matrix4X4  createTranslationMatrix(Vector translation) 
	{
		return Matrix4X4
		(
			1.0f, 0.0f, 0.0f, translation.X,
			0.0f, 1.0f, 0.0f, translation.Y,
			0.0f, 0.0f, 1.0f, translation.Z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	// Generate a view matrix for a camera based on the cameras position.
	inline Matrix4X4  createViewMatrix(Vector eyePos, Vector targetPos, Vector up) 
	{
		// The forward and right matracies.
		Vector forward = (targetPos - eyePos).normalise();
		Vector right = cross(forward, up).normalise();

		return Matrix4X4
		(
			right.X, right.Y, right.Z, -eyePos.X,
			forward.X, forward.Y, forward.Z, -eyePos.X,
			up.X, up.Y, up.Z, -eyePos.X,
			0.0f, 0.0f, 0.0f, 1.0f
		);

	};

	// generate a perspective matrix based on a provided FOV.
	inline Matrix4X4 createPerspectiveMatrix(float fovY, float aspectRatio, float nearZ, float farZ) 
	{
		return Matrix4X4
		(
			1 / (aspectRatio * tan(fovY / 2)),0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1 / tan(fovY / 2), 0.0f,
			0.0f ,0.0f, -((farZ + nearZ) / (farZ - nearZ)), -((2 * farZ * nearZ) / (farZ-nearZ)),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}
}