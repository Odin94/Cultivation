#include "stdafx.h"
#include "Tile.h"
#include "Globals.h"


Tile::Tile(int x, int y, TileTypes::Type type, int animFrames) : GameObject(x, y, globals::tileWidth, globals::tileHeight, Animation(TileTypes::spriteNames.at(type), animFrames, globals::tileWidth, globals::tileHeight)), type(type) {}
Tile::~Tile() {}


void Tile::findNeighbours(std::vector<std::vector<Tile>>& tiles)
{
	std::vector<Vec2d> neighbourShifts = { Vec2d(0, 1), Vec2d(1, 0), Vec2d(0, -1), Vec2d(-1, 0) };

	Vec2d ownVecPos = getIndex();
	if (int(ownVecPos.y) % 2 == 0) {
		neighbourShifts.push_back(Vec2d(-1, -1));
		neighbourShifts.push_back(Vec2d(-1, 1));
	}
	else {
		neighbourShifts.push_back(Vec2d(1, 1));
		neighbourShifts.push_back(Vec2d(1, -1));
	}

	for (const auto& shift : neighbourShifts) {
		Vec2d shifted = ownVecPos + shift;

		// if in vector bounds, add
		if (shifted.x >= 0 && shifted.y >= 0 && shifted.x < tiles.size() && shifted.y < tiles[shifted.x].size()) {
			neighbours.push_back(&tiles[shifted.x][shifted.y]);
		}
	}
}

int Tile::getCost()
{
	return TileTypes::costs.at(type);
}

bool Tile::isPassable()
{
	return (TileTypes::passable.at(type) && (occupyingActor == nullptr));
}

std::ostream& operator<<(std::ostream &strm, const Tile &tile) {
	Vec2d tilePos(int(tile.pos.x / tile.w), round(tile.pos.y / tile.h / globals::tileOffsetMultY));
	return strm << "TilePos: " << tilePos.x << ", " << tilePos.y;
}