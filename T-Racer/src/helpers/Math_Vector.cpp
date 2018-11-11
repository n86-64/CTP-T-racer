#include <math.h>
#include "Math_Vector.h"

namespace T_racer_Math 
{
	Vector3::Vector3(float x)
	{
		values[0] = x;
	}

	Vector3::Vector3(float x, float y) : Vector3::Vector3(x)
	{
		values[1] = y;
	}

	Vector3::Vector3(float x, float y, float z) : Vector3::Vector3(x, y)
	{
		values[2] = z;
	}

	Vector3::Vector3(const Vector3& vector)
	{
		this->values[0] = vector.values[0];
		this->values[1] = vector.values[1];
		this->values[2] = vector.values[2];
	}

	Vector3::Vector3(T_racer_Buffer buffer)
	{
		std::string dValue;
		size_t offset = 0;

		// Parse values out of the file stream.
		buffer.extractData(dValue, offset, '\n');
		X = stof(dValue);
		offset += dValue.size() + 1;

		dValue.clear();

		buffer.extractData(dValue, offset, '\n');
		Y = stof(dValue);
		offset += dValue.size() + 1;

		dValue.clear();

		buffer.extractData(dValue, offset, '\n');
		Z = stof(dValue);
	}

	Vector3 Vector3::operator+(Vector3 vec)
	{
		return Vector3(this->values[0] + vec.values[0], this->values[1] + vec.values[1], this->values[2] + vec.values[2]);
	}

	void Vector3::operator+=(Vector3 vec)
	{
		this->values[0] += vec.values[0];
		this->values[1] += vec.values[1];
		this->values[2] += vec.values[2];
	}

	Vector3 Vector3::operator-(Vector3 vec)
	{
		return Vector3(this->values[0] - vec.values[0], this->values[1] - vec.values[1], this->values[2] - vec.values[2]);
	}

	void Vector3::operator-=(Vector3 vec)
	{
		this->values[0] -= vec.values[0];
		this->values[1] -= vec.values[1];
		this->values[2] -= vec.values[2];
	}

	Vector3 Vector3::operator*(Vector3 vec)
	{
		return Vector3(this->values[0] * vec.values[0], this->values[1] * vec.values[1], this->values[2] * vec.values[2]);
	}

	void Vector3::operator*=(Vector3 vec)
	{
		this->values[0] *= vec.values[0];
		this->values[1] *= vec.values[1];
		this->values[2] *= vec.values[2];
	}

	Vector3 Vector3::operator/(Vector3 vec)
	{
		return Vector3(this->values[0] / vec.values[0], this->values[1] / vec.values[1], this->values[2] / vec.values[2]);
	}

	void Vector3::operator/=(Vector3 vec)
	{
		this->values[0] /= vec.values[0];
		this->values[1] /= vec.values[1];
		this->values[2] /= vec.values[2];
	}

	Vector3 Vector3::operator*(float scalier)
	{
		return Vector3(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
	}

	Vector3 Vector3::operator*(int scalier)
	{
		return Vector3(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
	}

	void Vector3::operator*=(float scalier)
	{
		this->values[0] *= scalier;
		this->values[1] *= scalier;
		this->values[2] *= scalier;
	}

	void Vector3::operator*=(int scalier)
	{
		this->values[0] *= scalier;
		this->values[1] *= scalier;
		this->values[2] *= scalier;
	}

	Vector3 Vector3::inverse(float scalier)
	{
		return Vector3(scalier / this->values[0], scalier / this->values[1], scalier / this->values[2]);
	}

	Vector3 Vector3::normalise()
	{
		float magnitude = Magnitude();
		return Vector3(this->values[0] / magnitude, this->values[1] / magnitude, this->values[2] / magnitude);
	}

	void Vector3::normaliseSelf()
	{
		float magnitude = Magnitude();
		this->values[0] /= magnitude;
		this->values[1] /= magnitude;
		this->values[2] /= magnitude;
	}

	float Vector3::normaliseSelfWithMagnitude()
	{
		float magnitude = Magnitude();
		this->values[0] /= magnitude;
		this->values[1] /= magnitude;
		this->values[2] /= magnitude;

		return magnitude;
	}

	float Vector3::Magnitude()
	{
		float value = pow(this->values[0], 2) + pow(this->values[1], 2) + pow(this->values[2], 2);
		return sqrt(value);
	}
}