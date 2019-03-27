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

void T_racer_Camera::getCameraCords(T_racer_Math::Vector& a, T_racer_Math::Vector& b, T_racer_Math::Vector& c)
{
	a = (position - (position + target)).normalise(); // view forward vector
	b = (T_racer_Math::cross(T_racer_Math::up, w)).normalise(); // right vector
	c = T_racer_Math::cross(w, u); // tup vector
}

float T_racer_Camera::cameraImportance(T_racer_Math::Vector camDirection)
{
	float theta;
	theta = fabsf(T_racer_Math::dot(camDirection, w)); // Use position + target if you need old state again.
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

	getCameraCords(w, u, v);

	lower_left_corner = T_racer_Math::Vector(-half_width, -half_height, -1.0f);
	lower_left_corner = position - u * half_width - v * half_height - w;
	horizontal = u * half_width * 2;
	vertical = v * half_height * 2;
	top = w + (v * half_height) + (u * half_width); 

	dx = u * (2.0f * (half_width / resX));
	dy = v * (2.0f * (half_height / resY));

	cameraPlane = T_racer_Math::dot(w, top);

	// Calculates camera A term.
	A = 2.0f * tanf(0.5f * fov); // May be converting fov to radians even though its already in radians. Need to confirm. 
	A *= A;
	A *= aspectRatio;
}

int T_racer_Camera::pixelPointOnCamera(T_racer_Math::Vector point)
{
	float t;
	T_racer_Math::Vector dirPoint;
	T_racer_Math::Vector vPlane;
	dirPoint = point - position;
	dirPoint.normaliseSelf();

	t = cameraPlane / fabsf(T_racer_Math::dot(dirPoint, w));
	dirPoint = dirPoint * t;
	//std::cout << "t value: " << t << "\n";
	dirPoint = -(dirPoint - top);

	int x = 0;
	int y = 0;
	vPlane = dirPoint / dx;
	x =T_racer_Math::firstPositiveInVec(dx, vPlane);
	vPlane = dirPoint / dy;
	y = T_racer_Math::firstPositiveInVec(dy, vPlane);

	int index = 0;

	if (x > -1 && x < resX && y > -1 && y < resY) 
	{
		return (y * (int)resX) + x;
	}
	else 
	{
		return -1;
	}
}
