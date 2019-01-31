#include "Camera.h"

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
