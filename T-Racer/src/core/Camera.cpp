#include "Camera.h"

void T_racer_Camera::init(jsoncons::key_value<std::string, jsoncons::json>& initValues)
{
	position = T_racer_Math::Vector(
		initValues.value()["Position"][0].as_double(),
		initValues.value()["Position"][1].as_double(),
		initValues.value()["Position"][2].as_double()
	);

	fov = radians(initValues.value()["fov"].as_double());
}

T_racer_CameraTransform T_racer_Camera::getCameraTransform()
{
	T_racer_CameraTransform  transform;
	transform.view = T_racer_Math::createViewMatrix(position, position + target, T_racer_Math::up);
	transform.projection = T_racer_Math::createPerspectiveMatrix(fov, getAspectRatio(), near, far);
	return transform;
}

void T_racer_Camera::getCameraCords(T_racer_Math::Vector& w, T_racer_Math::Vector& u, T_racer_Math::Vector& v)
{
	w = (position - (position + target)).normalise(); // view forward vector
	u = (T_racer_Math::cross(T_racer_Math::up, w)).normalise(); // top vector
	v = T_racer_Math::cross(w, u); // right vector
}

float T_racer_Camera::cameraImportance(T_racer_Math::Vector camDirection)
{
	float theta;
	theta = T_racer_Math::dot(camDirection, position + target);
	theta = theta * theta * theta;
	theta = A / theta;

	return theta;
}

void T_racer_Camera::setupCamera()
{
	// Shirley Method. 
	// position + target = forward view vector. Direction the camera is facing. 
	float aspectRatio = getAspectRatio();
	float theta = fov;
	float half_height = tan(theta / 2);
	float half_width = aspectRatio * half_height;

	T_racer_Math::Vector w, u, v;
	getCameraCords(w, u, v);

	lower_left_corner = T_racer_Math::Vector(-half_width, -half_height, -1.0f);
	lower_left_corner = position - u * half_width - v * half_height - w;
	horizontal = u * half_width * 2;
	vertical = v * half_height * 2;
	top = position + u * half_height + v; 

	cameraPlane = T_racer_Math::dot((position - (position + target)), top);

	// Calculates camera A term.
	A = 2.0f * tanf(0.5f * ((fov / 360.0f) * 2.0f * M_PI));
	A *= A;
	A *= aspectRatio;
}

int T_racer_Camera::pixelPointOnCamera(T_racer_Math::Vector point)
{
	float t;
	T_racer_Math::Vector dirPoint;
	T_racer_Math::Vector v;
	dirPoint = point - position;
	dirPoint.normalise();

	t = cameraPlane / T_racer_Math::dot(dirPoint, position + target);
	dirPoint = dirPoint * t;
	dirPoint = -(dirPoint - top);

	int x = 0;
	int y = 0;
	v = dirPoint / horizontal;
	x = T_racer_Math::firstPositiveInVec(horizontal, v);
	v = dirPoint / vertical;
	y = T_racer_Math::firstPositiveInVec(vertical, v);

	int index = 0;

	if (x > -1 && x < resX && y > -1 && y < resY) 
	{
		return  (y * (int)resX) + x;
	}
	else 
	{
		return -1;
	}
}
