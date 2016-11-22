#pragma once
#include "Vec2d.h"

class Camera
{
public:
	Camera(double offsetX = 0, double offsetY = 0);
	~Camera();

	Vec2d offset, tarOffset;
	double speed = 1.5;
	bool movingToTarget = false;

	void update(int elapsed);

	void moveTo(double tarX, double tarY);
	void moveTo(Vec2d tar);

	void jumpTo(double tarX, double tarY);
	void jumpTo(Vec2d tar);

	void moveBy(double x, double y);
	void moveBy(Vec2d offs);
};

