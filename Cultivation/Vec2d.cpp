#include "stdafx.h"
#include "Vec2d.h"
#include <math.h>

Vec2d::Vec2d(double x, double y) : x(x), y(y) {}
Vec2d::Vec2d(sf::Vector2i sfVec) : x(sfVec.x), y(sfVec.y) {};

Vec2d::~Vec2d() {}

void Vec2d::setLength(double newLength)
{
	double len = getLength();
	x /= len;
	y /= len;

	x *= newLength;
	y *= newLength;
}

double Vec2d::getLength()
{
	return sqrt(x * x + y * y);
}

double Vec2d::getDistance(Vec2d vec)
{
	return sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y));
}

void Vec2d::mult(double a)
{
	x *= a;
	y *= a;
}

void Vec2d::mult(Vec2d vec)
{
	x *= vec.x;
	y *= vec.y;
}
