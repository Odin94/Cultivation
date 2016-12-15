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
	bool highlighted = false;

	std::vector<Tile*> neighbours;
	Actor* occupyingActor;

	void findNeighbours(std::vector<std::vector<Tile>>& tiles);
	Vec2d getIndex();
	int getCost();

};

std::ostream& operator<<(std::ostream &strm, const Tile &tile);