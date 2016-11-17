#include "stdafx.h"
#include "GameState.h"
#include <iostream>

GameState::GameState()
{
	//For testing purposes!

	// fill 2 dimensional vector with tiles
	int w = 128;
	int h = 128;
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