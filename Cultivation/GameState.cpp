#include "stdafx.h"
#include "GameState.h"
#include <iostream>
#include "Globals.h"

GameState::GameState()
{
	//For testing purposes!

	// fill 2 dimensional vector with tiles
	int w = globals::tileWidth;
	int h = globals::tileHeight;
	for (int i = 0; i < 20; i++) {
		std::vector<Tile> tileRow;
		for (int j = 0; j < 20; j++) {
			if (j % 2 == 0) {
				tileRow.push_back(Tile(i * w, j * h * 0.75));
			}
			else {
				tileRow.push_back(Tile(i * w + w * 0.5, j * h * 0.75));
			}
		}
		tiles.push_back(tileRow);
	}

	for (auto& tileRow : tiles) {
		for (auto& tile : tileRow) {
			tile.findNeighbours(tiles);
		}
	}

	// create some actors
	for (int i = 0; i < 5; i++) {
		actors.push_back(Actor(i * 128, 0));
	}
}


GameState::~GameState()
{
}

void GameState::update(int elapsed)
{
	for (auto& actor : actors) {
		actor.update(elapsed);
	}
}
