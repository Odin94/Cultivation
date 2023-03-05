#pragma once
#include "GameObject.h"
#include <vector>
#include "TileTypes.h"

class Tile : public GameObject {
public:
	Tile(int x, int y, TileTypes::Type type = TileTypes::Type::plains, int animFrames = 1);
	~Tile();

	bool highlighted = false;
	TileTypes::Type type;

	std::vector<Tile *> neighbours;
	GameObject *occupyingObject = nullptr;

	void RMBAction(GameObject &obj) override;

	void findNeighbours(std::vector<std::vector<Tile>> &tiles);
	int getCost();
	bool isPassable();

	Vec2d getCenter();
};

std::ostream &operator<<(std::ostream &strm, const Tile &tile);