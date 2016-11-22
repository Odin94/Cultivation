#pragma once
#include "Vec2d.h"

class Actor;

class Tile
{
public:
	Tile(int x, int y);
	~Tile();

	Vec2d pos;
	int w, h;
	Actor* occupyingActor;

};

