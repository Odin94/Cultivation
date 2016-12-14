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

	const bool operator==(const Vec2d& vec) const {
		return (x == vec.x && y == vec.y);
	}

	bool operator!=(const Vec2d& vec) {
		return !(*this == vec);
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

	Vec2d operator+(const Vec2d& vec) {
		return Vec2d(x + vec.x, y + vec.y);
	}
};

namespace std {
	template <> struct hash<Vec2d>
	{
		size_t operator()(const Vec2d & vec) const
		{
			// uniquely map two ints to one
			int x_hash, y_hash;

			if (vec.x < 0) {
				x_hash = -vec.x * 2 - 1;
			}
			else {
				x_hash = vec.x * 2;
			}

			if (vec.y < 0) {
				y_hash = -vec.y * 2 - 1;
			}
			else {
				y_hash = vec.y * 2;
			}

			int pairedInt = 0.5 * (x_hash + y_hash)*(x_hash + y_hash + 1) + y_hash; // cantor pairing
			return hash<int>()(pairedInt);
		}
	};
}

