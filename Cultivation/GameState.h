#pragma once

#include <string>
#include <vector>
#include "Tile.h"
#include "Actor.h"

class GameState
{
public:
	GameState();
	~GameState();

	void update(int elapsed);

	//TODO: put stuff in subclasses for different states - or put it in a global world class?
	std::vector<std::vector<Tile>> tiles;
	std::vector<Actor> actors;
};

