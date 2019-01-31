#include <math.h>
#include "Math_Vector.h"

namespace T_racer_Math 
{
	Vector::Vector(float x)
	{
		values[0] = x;
	}

	Vector::Vector(float x, float y) : Vector::Vector(x)
	{
		values[1] = y;
	}

	Vector::Vector(float x, float y, float z) : Vector::Vector(x, y)
	{
		values[2] = z;
	}

	Vector::Vector(float x, float y, float z, float w) : Vector::Vector(x, y, z)
	{
		values[3] = w;
	}

	Vector::Vector(const Vector& vector)
	{
		this->values[0] = vector.values[0];
		this->values[1] = vector.values[1];
		this->values[2] = vector.values[2];
	}

	float Vector::maxComp()
	{
		float max = (-INFINITY);
		for (int i = 0; i < 3; i++) 
		{
			if (values[i] > max) 
			{
				max = values[i];
			}
		}
		return max;
	}

	float Vector::minComp()
	{
		float min = INFINITY;
		for (int i = 0; i < 3; i++)
		{
			if (values[i] < min)
			{
				min = values[i];
			}
		}
		return min;
	}

	Vector Vector::operator+(Vector vec)
	{
		return Vector(this->values[0] + vec.values[0], this->values[1] + vec.values[1], this->values[2] + vec.values[2]);
	}

	void Vector::operator+=(Vector vec)
	{
		this->values[0] += vec.values[0];
		this->values[1] += vec.values[1];
		this->values[2] += vec.values[2];
	}

	Vector Vector::operator-(Vector vec)
	{
		return Vector(this->values[0] - vec.values[0], this->values[1] - vec.values[1], this->values[2] - vec.values[2]);
	}

	Vector Vector::operator-()
	{
		return Vector(-this->values[0], -this->values[1], -this->values[2]);
	}

	void Vector::operator-=(Vector vec)
	{
		this->values[0] -= vec.values[0];
		this->values[1] -= vec.values[1];
		this->values[2] -= vec.values[2];
	}

	Vector Vector::operator*(Vector vec)
	{
		return Vector(this->values[0] * vec.values[0], this->values[1] * vec.values[1], this->values[2] * vec.values[2]);
	}

	void Vector::operator*=(Vector vec)
	{
		this->values[0] *= vec.values[0];
		this->values[1] *= vec.values[1];
		this->values[2] *= vec.values[2];
	}

	Vector Vector::operator/(Vector vec)
	{
		return Vector(this->values[0] / vec.values[0], this->values[1] / vec.values[1], this->values[2] / vec.values[2]);
	}

	void Vector::operator/=(Vector vec)
	{
		this->values[0] /= vec.values[0];
		this->values[1] /= vec.values[1];
		this->values[2] /= vec.values[2];
	}

	Vector Vector::operator/(int scalier)
	{
		return Vector(this->values[0] / scalier, this->values[1] / scalier, this->values[2] / scalier);
	}

	Vector Vector::operator/(float scalier)
	{
		return Vector(this->values[0] / scalier, this->values[1] / scalier, this->values[2] / scalier);
	}

	Vector Vector::operator*(float scalier)
	{
		return Vector(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
	}

	Vector Vector::operator*(int scalier)
	{
		return Vector(this->values[0] * scalier, this->values[1] * scalier, this->values[2] * scalier);
	}

	void Vector::operator*=(float scalier)
	{
		this->values[0] *= scalier;
		this->values[1] *= scalier;
		this->values[2] *= scalier;
	}

	void Vector::operator*=(int scalier)
	{
		this->values[0] *= scalier;
		this->values[1] *= scalier;
		this->values[2] *= scalier;
	}

	Vector Vector::inverse(float scalier)
	{
		return Vector(scalier / this->values[0], scalier / this->values[1], scalier / this->values[2]);
	}

	Vector Vector::normalise()
	{
		float magnitude = Magnitude();
		return Vector(this->values[0] / magnitude, this->values[1] / magnitude, this->values[2] / magnitude);
	}

	void Vector::normaliseSelf()
	{
		float magnitude = Magnitude();
		this->values[0] /= magnitude;
		this->values[1] /= magnitude;
		this->values[2] /= magnitude;
	}

	float Vector::normaliseSelfWithMagnitude()
	{
		float magnitude = Magnitude();
		this->values[0] /= magnitude;
		this->values[1] /= magnitude;
		this->values[2] /= magnitude;

		return magnitude;
	}

	float Vector::Magnitude()
	{
		float value = (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]);
		return sqrt(value);
	}

	float Vector::MagnitudeSq()
	{
		float value = (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]);
		return value;
	}
}