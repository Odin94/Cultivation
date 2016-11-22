#include "stdafx.h"
#include "Camera.h"


Camera::Camera(double offsetX, double offsetY) : offset(Vec2d(offsetX, offsetY)), tarOffset(offset) {}


Camera::~Camera() {}

void Camera::update(int elapsed)
{
	if (offset == tarOffset) {
		movingToTarget = false;
	}

	if (movingToTarget) {
		Vec2d vel = tarOffset - offset;
		vel.setLength(speed * elapsed);

		offset += vel;

		if (offset.getDistance(tarOffset) < vel.getLength()) {
			offset = tarOffset;
		}
	}
}

void Camera::moveTo(double tarX, double tarY)
{
	moveTo(Vec2d(tarX, tarY));
}


void Camera::moveTo(Vec2d tar)
{
	tarOffset = tar;
	movingToTarget = true;
}

void Camera::jumpTo(double tarX, double tarY)
{
	jumpTo(Vec2d(tarX, tarY));
}

void Camera::jumpTo(Vec2d tar)
{
	offset = tar;
}

void Camera::moveBy(double x, double y)
{
	moveBy(Vec2d(x, y));
}

void Camera::moveBy(Vec2d offs)
{
	offset += offs;
}
