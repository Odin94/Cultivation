#include "stdafx.h"
#include "Camera.h"


Camera::Camera(double offsetX, double offsetY) : offsetX(offsetX), offsetY(offsetY) {}


Camera::~Camera() {}

// TODO: use Vec2d pos instead of two doubles
// TODO: make this move smoothly instead of jumping
void Camera::moveTo(double tarX, double tarY)
{
	offsetX = tarX;
	offsetY = tarY;
}

void Camera::jumpTo(double tarX, double tarY)
{
	offsetX = tarX;
	offsetY = tarY;
}

void Camera::moveBy(double x, double y)
{
	offsetX += x;
	offsetY += y;
}
