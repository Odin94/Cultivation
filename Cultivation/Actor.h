#pragma once
#include "Tile.h"
#include "Vec2d.h"
#include <deque>

class Actor
{
public:
	Actor(double x, double y);
	~Actor();

	Vec2d pos, tar;
	double speed = 1;
	int w, h;

	std::deque<Tile*> tarPath;

	void findPathAndMoveTo(Tile& tile);
	void moveTo(Tile& tile);
	void update(int elapsed);
	Vec2d getIndex();

};

