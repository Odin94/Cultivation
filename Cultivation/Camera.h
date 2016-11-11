#pragma once
class Camera
{
public:
	Camera(double offsetX = 0, double offsetY = 0);
	~Camera();

	double offsetX, offsetY;

	void moveTo(double tarX, double tarY);
	void jumpTo(double tarX, double tarY);

	void moveBy(double x, double y);
};

