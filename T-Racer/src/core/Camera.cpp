#include "Camera.h"

T_racer_CameraTransform Camera::getCameraTransform()
{
	T_racer_CameraTransform  transform;
	transform.view = T_racer_Math::createViewMatrix(position, target, T_racer_Math::up);
	transform.projection = T_racer_Math::createPerspectiveMatrix(fov, resX / resY, near, far);
	return transform;
}
