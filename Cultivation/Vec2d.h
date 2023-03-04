#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Vec2d
{
public:
	Vec2d();
	Vec2d(double x, double y);
	Vec2d(sf::Vector2i sfVec);
	~Vec2d();

	double x, y;

	void setLength(double newLength);
	double getLength();
	double getDistance(Vec2d vec);

	void mult(double a);
	void mult(Vec2d vec);

	bool operator==(const Vec2d &vec)
	{
		return (x == vec.x && y == vec.y);
	}

	const bool operator==(const Vec2d &vec) const
	{
		return (x == vec.x && y == vec.y);
	}

	bool operator!=(const Vec2d &vec)
	{
		return !(*this == vec);
	}

	Vec2d &operator+=(const Vec2d &vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vec2d &operator-=(const Vec2d &vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vec2d operator-(const Vec2d &vec)
	{
		return Vec2d(x - vec.x, y - vec.y);
	}

	Vec2d operator+(const Vec2d &vec)
	{
		return Vec2d(x + vec.x, y + vec.y);
	}
};

std::ostream &operator<<(std::ostream &strm, const Vec2d &vec);

namespace std
{
	template <>
	struct hash<Vec2d>
	{
		size_t operator()(const Vec2d &vec) const
		{
			// uniquely map two ints to one
			int x_hash, y_hash;

			if (vec.x < 0)
			{
				x_hash = int(-vec.x * 2 - 1);
			}
			else
			{
				x_hash = int(vec.x * 2);
			}

			if (vec.y < 0)
			{
				y_hash = int(-vec.y * 2 - 1);
			}
			else
			{
				y_hash = int(vec.y * 2);
			}

			// cantor pairing; NOTE: This is int only afaik, which is fine for my use case but might be an issue in other contexts
			int pairedInt = int(0.5 * (x_hash + y_hash) * (x_hash + y_hash + 1) + y_hash);
			return hash<int>()(pairedInt);
		}
	};
}
