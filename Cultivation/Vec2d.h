#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vec2d
{
public:
	Vec2d(double x, double y);
	Vec2d::Vec2d(sf::Vector2i sfVec);
	~Vec2d();

	double x, y;

	void setLength(double newLength);
	double getLength();
	double getDistance(Vec2d vec);

	void mult(double a);
	void mult(Vec2d vec);

	bool operator==(const Vec2d& vec) {
		return (x == vec.x && y == vec.y);
	}

	bool operator!=(const Vec2d& vec) {
		return (x != vec.x || y != vec.y);
	}

	Vec2d& operator+=(const Vec2d& vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vec2d& operator-=(const Vec2d& vec) {
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vec2d operator-(const Vec2d& vec) {
		return Vec2d(x - vec.x, y - vec.y);
	}
};

