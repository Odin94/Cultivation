#include "stdafx.h"
#include "Tile.h"
#include "Globals.h"


Tile::Tile(int x, int y) : pos(Vec2d(x, y)), w(globals::tileWidth), h(globals::tileHeight) {}


Tile::~Tile() {}

void Tile::findNeighbours(std::vector<std::vector<Tile>>& tiles)
{
	std::vector<Vec2d> neighbourShifts = { Vec2d(0, 1), Vec2d(-1, 1), Vec2d(1, 0), Vec2d(0, -1), Vec2d(1, -1), Vec2d(-1, 0) };
	Vec2d ownVecPos = Vec2d(pos.x / w, pos.y / h);

	for (const auto& shift : neighbourShifts) {
		Vec2d shifted = ownVecPos + shift;

		// if out of vector bounds, continue
		if (shifted.x >= 0 && shifted.y >= 0 && shifted.x < tiles.size() && shifted.y < tiles[shifted.x].size()) {
			neighbours.push_back(&tiles[shifted.x][shifted.y]);
		}
	}
}

