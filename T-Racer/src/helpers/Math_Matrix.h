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
constexpr int MATRIX_ELEMENTS_COUNT_3X3 = 9;

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

		void value(int row, int column, float value) 
		{
			m[row][column] = value;
		}

		// matrix operations
		Vector    operator* (Vector mat);
		Matrix4X4 operator*(Matrix4X4 matrix);
		float&    operator[](int pos) { return matrix[pos]; }


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

	class Matrix3X3 
	{
	public:
		Matrix3X3() = default;
		Matrix3X3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		};

		// Return a value from the matrix.
		float value(int row, int column)
		{
			return m[row][column];
		}

		void value(int row, int column, float value)
		{
			m[row][column] = value;
		}


		Vector operator*(Vector v);

	private:
		union
		{
			// Initialy set to be an identity matrix.
			float matrix[MATRIX_ELEMENTS_COUNT_3X3] =
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
			float m[3][3];
		};
	};

	// Matrix constants
	const Matrix4X4 ERROR_MATRIX_4X4
	(
		INFINITY, INFINITY, INFINITY, INFINITY,
		INFINITY, INFINITY, INFINITY, INFINITY,
		INFINITY, INFINITY, INFINITY, INFINITY,
		INFINITY, INFINITY, INFINITY, INFINITY
	);

	const Matrix3X3 ERROR_MATRIX_3X3
	(
		INFINITY, INFINITY, INFINITY,
		INFINITY, INFINITY, INFINITY,
		INFINITY, INFINITY, INFINITY
	);

	inline float getMatrixDeterminant(Matrix4X4 mat) 
	{
		float d1 = mat.value(0, 0) + mat.value(1, 1) + mat.value(2, 2) + mat.value(3, 3);
		float d2 = mat.value(3, 0) + mat.value(2, 1) + mat.value(1, 2) + mat.value(0, 3);

		return ((d1 - d2));
	}

	// Returns the input matrix if the operation fails.
	inline Matrix4X4 getInverseMatrix(Matrix4X4 mat) 
	{
		// perform gauss-jordan matrix inversion.
		T_racer_Math::Matrix4X4   inverseMatrix;
		float inverseValue;
		float d = 0.0f; // = getMatrixDeterminant(mat);


		//if (d == 0.0f) 
		//{
		//	// there is no determinant. Return error matrix.
		//	return ERROR_MATRIX;
		//}

		// TODO - Finsih implementation of gauss-Jorden inversion.
		//for (int r = 0; r < 4; r++) 
		//{
		//	if (mat.value(r, r) != 1.0f) 
		//	{
		//		for (int i = 0; i < 4; i++) 
		//		{
		//			mat.value(r, i, mat.value(r, i) / mat.value(r, 0));
		//		}

		//		for (int i = 0; i < 4; i++)
		//		{
		//			inverseMatrix.value(r, i, mat.value(r, i) / mat.value(r, 0));
		//		}
		//	}

		//	inverseValue = -mat.value(r + 1, r);

		//	// Now we calculate the pivots.
		//	for (int r2 = 0; r2 < 4; r2++) 
		//	{
		//		if (r2 != r) 
		//		{
		//			// perform the calculation.
		//			for (int c2 = 0; c2 < 4; c2++) 
		//			{
		//				mat.value(r2, c2, (mat.value(r2, c2) - inverseValue) * mat.value(r2 - 1, c2));
		//			}
		//		}
		//	}
		//}
		
		// Source code retrieved from GLU project (OpenGL utility Library.) - https://github.com/jlyharia/Computer_GraphicsII/blob/master/gluInvertMatrix.h
		inverseMatrix[0] = mat[5] * mat[10] * mat[15] -
			mat[5] * mat[11] * mat[14] -
			mat[9] * mat[6] * mat[15] +
			mat[9] * mat[7] * mat[14] +
			mat[13] * mat[6] * mat[11] -
			mat[13] * mat[7] * mat[10];

		inverseMatrix[4] = -mat[4] * mat[10] * mat[15] +
			mat[4] * mat[11] * mat[14] +
			mat[8] * mat[6] * mat[15] -
			mat[8] * mat[7] * mat[14] -
			mat[12] * mat[6] * mat[11] +
			mat[12] * mat[7] * mat[10];

		inverseMatrix[8] = mat[4] * mat[9] * mat[15] -
			mat[4] * mat[11] * mat[13] -
			mat[8] * mat[5] * mat[15] +
			mat[8] * mat[7] * mat[13] +
			mat[12] * mat[5] * mat[11] -
			mat[12] * mat[7] * mat[9];

		inverseMatrix[12] = -mat[4] * mat[9] * mat[14] +
			mat[4] * mat[10] * mat[13] +
			mat[8] * mat[5] * mat[14] -
			mat[8] * mat[6] * mat[13] -
			mat[12] * mat[5] * mat[10] +
			mat[12] * mat[6] * mat[9];

		inverseMatrix[1] = -mat[1] * mat[10] * mat[15] +
			mat[1] * mat[11] * mat[14] +
			mat[9] * mat[2] * mat[15] -
			mat[9] * mat[3] * mat[14] -
			mat[13] * mat[2] * mat[11] +
			mat[13] * mat[3] * mat[10];

		inverseMatrix[5] = mat[0] * mat[10] * mat[15] -
			mat[0] * mat[11] * mat[14] -
			mat[8] * mat[2] * mat[15] +
			mat[8] * mat[3] * mat[14] +
			mat[12] * mat[2] * mat[11] -
			mat[12] * mat[3] * mat[10];

		inverseMatrix[9] = -mat[0] * mat[9] * mat[15] +
			mat[0] * mat[11] * mat[13] +
			mat[8] * mat[1] * mat[15] -
			mat[8] * mat[3] * mat[13] -
			mat[12] * mat[1] * mat[11] +
			mat[12] * mat[3] * mat[9];

		inverseMatrix[13] = mat[0] * mat[9] * mat[14] -
			mat[0] * mat[10] * mat[13] -
			mat[8] * mat[1] * mat[14] +
			mat[8] * mat[2] * mat[13] +
			mat[12] * mat[1] * mat[10] -
			mat[12] * mat[2] * mat[9];

		inverseMatrix[2] = mat[1] * mat[6] * mat[15] -
			mat[1] * mat[7] * mat[14] -
			mat[5] * mat[2] * mat[15] +
			mat[5] * mat[3] * mat[14] +
			mat[13] * mat[2] * mat[7] -
			mat[13] * mat[3] * mat[6];

		inverseMatrix[6] = -mat[0] * mat[6] * mat[15] +
			mat[0] * mat[7] * mat[14] +
			mat[4] * mat[2] * mat[15] -
			mat[4] * mat[3] * mat[14] -
			mat[12] * mat[2] * mat[7] +
			mat[12] * mat[3] * mat[6];

		inverseMatrix[10] = mat[0] * mat[5] * mat[15] -
			mat[0] * mat[7] * mat[13] -
			mat[4] * mat[1] * mat[15] +
			mat[4] * mat[3] * mat[13] +
			mat[12] * mat[1] * mat[7] -
			mat[12] * mat[3] * mat[5];

		inverseMatrix[14] = -mat[0] * mat[5] * mat[14] +
			mat[0] * mat[6] * mat[13] +
			mat[4] * mat[1] * mat[14] -
			mat[4] * mat[2] * mat[13] -
			mat[12] * mat[1] * mat[6] +
			mat[12] * mat[2] * mat[5];

		inverseMatrix[3] = -mat[1] * mat[6] * mat[11] +
			mat[1] * mat[7] * mat[10] +
			mat[5] * mat[2] * mat[11] -
			mat[5] * mat[3] * mat[10] -
			mat[9] * mat[2] * mat[7] +
			mat[9] * mat[3] * mat[6];

		inverseMatrix[7] = mat[0] * mat[6] * mat[11] -
			mat[0] * mat[7] * mat[10] -
			mat[4] * mat[2] * mat[11] +
			mat[4] * mat[3] * mat[10] +
			mat[8] * mat[2] * mat[7] -
			mat[8] * mat[3] * mat[6];

		inverseMatrix[11] = -mat[0] * mat[5] * mat[11] +
			mat[0] * mat[7] * mat[9] +
			mat[4] * mat[1] * mat[11] -
			mat[4] * mat[3] * mat[9] -
			mat[8] * mat[1] * mat[7] +
			mat[8] * mat[3] * mat[5];

		inverseMatrix[15] = mat[0] * mat[5] * mat[10] -
			mat[0] * mat[6] * mat[9] -
			mat[4] * mat[1] * mat[10] +
			mat[4] * mat[2] * mat[9] +
			mat[8] * mat[1] * mat[6] -
			mat[8] * mat[2] * mat[5];

		d = (mat[0] * inverseMatrix[0]) + (mat[1] * inverseMatrix[4]) + (mat[2] * inverseMatrix[8]) + (mat[3] * inverseMatrix[12]);

		if (d == 0.0f) 
		{
			return ERROR_MATRIX_4X4;
		}

		d = 1 / d;
		for (int i = 0; i < MATRIX_ELEMENTS_COUNT_4X4; i++) 
		{
			inverseMatrix[i] *= d;
		}

		return inverseMatrix;
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

	// Generates a scale matrix.
	inline Matrix4X4 createScaleMatrix(Vector scale) 
	{
		return Matrix4X4
		(
			scale.X, 0.0f, 0.0f, 0.0f,
			0.0f, scale.Y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.Z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	// Generate a view matrix for a camera based on the cameras position.
	inline Matrix4X4  createViewMatrix(Vector eyePos, Vector targetPos, Vector up) 
	{
		// TODO - Review this matrix in order to solve issues with camera and possibly BVH.
		// The forward and right matracies.
		Vector forward = (targetPos - eyePos).normalise();
		Vector right = cross(forward, up).normalise();
		Vector lUp = cross(right, forward);
		
		return Matrix4X4
		(
			forward.X, lUp.X, right.X, 0.0f,
			forward.Y, lUp.Y, right.Y, 0.0f,
			forward.Z, lUp.Z, right.Z, 0.0f,
			-dot(forward, eyePos), -dot(lUp, eyePos), -dot(right, eyePos), 1.0f
		);

	};

	// generate a perspective matrix based on a provided FOV.
	inline Matrix4X4 createPerspectiveMatrix(float fovY, float aspectRatio, float nearZ, float farZ) 
	{
		// Based on DirectX Implementation.
		float yScale = 1 / tan(fovY / 2);
		float xScale = yScale / aspectRatio;

		return createScaleMatrix(T_racer_Math::Vector(xScale, yScale, 1.0f)) *
			Matrix4X4
			(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, farZ / (farZ - nearZ), -(nearZ*farZ) / (farZ - nearZ),
				0.0f, 0.0f, 1.0f, 0.0f
			);


		//return Matrix4X4
		//(
		//	1 / (aspectRatio * tan(fovY / 2)),0.0f, 0.0f, 0.0f,
		//	0.0f, 0.0f, 1 / tan(fovY / 2), 0.0f,
		//	0.0f ,0.0f, -((farZ + nearZ) / (farZ - nearZ)), -((2 * farZ * nearZ) / (farZ-nearZ)),
		//	0.0f, 0.0f, -1.0f, 0.0f
		//);
	}
}