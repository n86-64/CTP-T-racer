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
	w = (position - (position + target)).normalise();
	u = (T_racer_Math::cross(T_racer_Math::up, w)).normalise();
	v = T_racer_Math::cross(w, u);
}

float T_racer_Camera::cameraImportance(T_racer_Math::Vector camDirection)
{
	float theta;
	theta = T_racer_Math::dot(camDirection, position + target);
	theta = theta * theta * theta;
	theta = A / theta;

	return theta;
}
