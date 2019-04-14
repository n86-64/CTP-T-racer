#include "Math_Matrix.h"

T_racer_Math::Vector T_racer_Math::Matrix4X4::operator*(Vector mat)
{
	return T_racer_Math::Vector
	(
		(value(0, 0) * mat.X) + (value(0, 1) * mat.Y) + (value(0, 2) * mat.Z) + (value(0, 3) * mat.W),
		(value(1, 0) * mat.X) + (value(1, 1) * mat.Y) + (value(1, 2) * mat.Z) + (value(1, 3) * mat.W),
		(value(2, 0) * mat.X) + (value(2, 1) * mat.Y) + (value(2, 2) * mat.Z) + (value(2, 3) * mat.W),
		(value(3, 0) * mat.X) + (value(3, 1) * mat.Y) + (value(3, 2) * mat.Z) + (value(3, 3) * mat.W)
	);
}

T_racer_Math::Matrix4X4 T_racer_Math::Matrix4X4::operator*(Matrix4X4 matrix)
{
	T_racer_Math::Matrix4X4  Rmatrix;

	Rmatrix.m[0][0] = (value(0, 0) * value(0, 0)) + (value(0, 1) * value(1, 0)) + (value(0, 2) * value(2, 0)) + (value(0, 3) * value(3, 0));
	Rmatrix.m[1][0] = (value(1, 0) * value(0, 0)) + (value(1, 1) * value(1, 0)) + (value(1, 2) * value(2, 0)) + (value(1, 3) * value(3, 0));
	Rmatrix.m[2][0] = (value(2, 0) * value(0, 0)) + (value(2, 1) * value(1, 0)) + (value(2, 2) * value(2, 0)) + (value(2, 3) * value(3, 0));
	Rmatrix.m[3][0] = (value(3, 0) * value(0, 0)) + (value(3, 1) * value(1, 0)) + (value(3, 2) * value(2, 0)) + (value(3, 3) * value(3, 0));

	Rmatrix.m[0][1] = (value(0, 0) * value(0, 1)) + (value(0, 1) * value(1, 1)) + (value(0, 2) * value(2, 1)) + (value(0, 3) * value(3, 1));
	Rmatrix.m[1][1] = (value(1, 0) * value(0, 1)) + (value(1, 1) * value(1, 1)) + (value(1, 2) * value(2, 1)) + (value(1, 3) * value(3, 1));
	Rmatrix.m[2][1] = (value(2, 0) * value(0, 1)) + (value(2, 1) * value(1, 1)) + (value(2, 2) * value(2, 1)) + (value(2, 3) * value(3, 1));
	Rmatrix.m[3][1] = (value(3, 0) * value(0, 1)) + (value(3, 1) * value(1, 1)) + (value(3, 2) * value(2, 1)) + (value(3, 3) * value(3, 1));

	Rmatrix.m[0][2] = (value(0, 0) * value(0, 2)) + (value(0, 1) * value(1, 2)) + (value(0, 2) * value(2, 2)) + (value(0, 3) * value(3, 2));
	Rmatrix.m[1][2] = (value(1, 0) * value(0, 2)) + (value(1, 1) * value(1, 2)) + (value(1, 2) * value(2, 2)) + (value(1, 3) * value(3, 2));
	Rmatrix.m[2][2] = (value(2, 0) * value(0, 2)) + (value(2, 1) * value(1, 2)) + (value(2, 2) * value(2, 2)) + (value(2, 3) * value(3, 2));
	Rmatrix.m[3][2] = (value(3, 0) * value(0, 2)) + (value(3, 1) * value(1, 2)) + (value(3, 2) * value(2, 2)) + (value(3, 3) * value(3, 2));

	Rmatrix.m[0][3] = (value(0, 0) * value(0, 3)) + (value(0, 1) * value(1, 3)) + (value(0, 2) * value(2, 3)) + (value(0, 3) * value(3, 3));
	Rmatrix.m[1][3] = (value(1, 0) * value(0, 3)) + (value(1, 1) * value(1, 3)) + (value(1, 2) * value(2, 3)) + (value(1, 3) * value(3, 3));
	Rmatrix.m[2][3] = (value(2, 0) * value(0, 3)) + (value(2, 1) * value(1, 3)) + (value(2, 2) * value(2, 3)) + (value(2, 3) * value(3, 3));
	Rmatrix.m[3][3] = (value(3, 0) * value(0, 3)) + (value(3, 1) * value(1, 3)) + (value(3, 2) * value(2, 3)) + (value(3, 3) * value(3, 3));

	return Rmatrix;
}

T_racer_Math::Vector T_racer_Math::Matrix3X3::operator*(T_racer_Math::Vector v)
{
	return Vector
	(
		m[0][0] * v.X + m[0][1] * v.Y + m[0][2] * v.Z,
		m[1][0] * v.X + m[1][1] * v.Y + m[1][2] * v.Z,
		m[2][0] * v.X + m[2][1] * v.Y + m[2][2] * v.Z
	);
}
