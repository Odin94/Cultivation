#pragma once
#include "Vec2d.h"
#include <vector>

class Actor;

class Tile
{
public:
	Tile(int x, int y);
	~Tile();

	Vec2d pos;
	int w, h;

	std::vector<Tile*> neighbours;
	Actor* occupyingActor;

	void findNeighbours(std::vector<std::vector<Tile>>& tiles);
};

