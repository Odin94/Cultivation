#pragma once
#include "Vec2d.h"
#include <vector>
#include "TileTypes.h"

class Actor;

class Tile
{
public:
	Tile(int x, int y, TileTypes::Type type = TileTypes::Type::plains);
	~Tile();

	Vec2d pos;
	int w, h;
	bool highlighted = false;
	TileTypes::Type type;

	std::vector<Tile*> neighbours;
	Actor* occupyingActor;

	void findNeighbours(std::vector<std::vector<Tile>>& tiles);
	Vec2d getIndex();
	int getCost();
	bool isPassable();

};

std::ostream& operator<<(std::ostream &strm, const Tile &tile);