#pragma once

#include <string>
#include <vector>
#include "Tile.h"
#include "Actor.h"
#include "Building.h"

// singleton
class GameState
{
public:
	static GameState& getInstance() {
		static GameState instance; // instantiated on first use
		return instance;
	}

	// can't be copied or assigned
	GameState(GameState const&) = delete;
	void operator=(GameState const&) = delete;

	void update(int elapsed);

	std::vector<std::vector<Tile>> tiles;
	std::vector<Actor> actors;
	std::vector<Building> buildings;

private:
	GameState();
};

