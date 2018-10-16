#include <math.h>
#include "Math_Vector.h"

T_racer_Vector3::T_racer_Vector3(float x)
{
	values[0] = x;
}

T_racer_Vector3::T_racer_Vector3(float x, float y) : T_racer_Vector3::T_racer_Vector3(x)
{
	values[1] = y;
}

T_racer_Vector3::T_racer_Vector3(float x, float y, float z) : T_racer_Vector3::T_racer_Vector3(x,y)
{
	values[2] = z;
}

T_racer_Vector3::T_racer_Vector3(const T_racer_Vector3& vector)
{
	this->values[0] = vector.values[0];
	this->values[1] = vector.values[1];
	this->values[2] = vector.values[2];
}	

T_racer_Vector3 T_racer_Vector3::operator+(T_racer_Vector3 vec) 
{
	return T_racer_Vector3(this->values[0] + vec.values[0], this->values[1] + vec.values[1], this->values[2] + vec.values[2]);
}

void T_racer_Vector3::operator+=(T_racer_Vector3 vec)
{
	for (int i = 0; i < 3; i++)
	{
		this->values[i] += vec.values[i];
	}
}

T_racer_Vector3 T_racer_Vector3::operator-(T_racer_Vector3 vec)
{
	return T_racer_Vector3(this->values[0] - vec.values[0], this->values[1] - vec.values[1], this->values[2] - vec.values[2]);
}

void T_racer_Vector3::operator-=(T_racer_Vector3 vec)
{
	for (int i = 0; i < 3; i++)
	{
		this->values[i] -= vec.values[i];
	}
}


T_racer_Vector3 T_racer_Vector3::operator*(float scalier) 
{
	return T_racer_Vector3(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
}

T_racer_Vector3 T_racer_Vector3::operator*(int scalier)
{
	return T_racer_Vector3(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
}

void T_racer_Vector3::operator*=(float scalier)
{
	for (int i = 0; i < 3; i++)
	{
		this->values[i] *= scalier;
	}
}

void T_racer_Vector3::operator*=(int scalier)
{
	for (int i = 0; i < 3; i++) 
	{
		this->values[i] *= scalier;
	}
}

T_racer_Vector3 T_racer_Vector3::normalise()
{
	float magnitude = calcualteMagnitude();
	return T_racer_Vector3(this->values[0] / magnitude, this->values[1] / magnitude, this->values[2] / magnitude);
}

float T_racer_Vector3::calcualteMagnitude()
{
	float value = pow(this->values[0], 2) + pow(this->values[1], 2) + pow(this->values[2], 2);
	return sqrt(value);
}

