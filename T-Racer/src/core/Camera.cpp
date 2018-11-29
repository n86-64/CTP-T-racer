#include "Camera.h"

T_racer_CameraTransform T_racer_Camera::getCameraTransform()
{
	T_racer_CameraTransform  transform;
	transform.view = T_racer_Math::createViewMatrix(position, position + target, T_racer_Math::up);
	transform.projection = T_racer_Math::createPerspectiveMatrix(fov, getAspectRatio(), near, far);
	return transform;
}
