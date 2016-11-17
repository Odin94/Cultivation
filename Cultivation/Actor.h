#pragma once
#include "Tile.h"
#include "Vec2d.h"

class Actor
{
public:
	Actor(double x, double y);
	~Actor();

	Vec2d pos, tar;
	double speed = 1;
	int w, h;

	void moveTo(Tile& tile);
	void update(int elapsed);

};

