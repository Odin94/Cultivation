#include "stdafx.h"
#include "GameState.h"
#include <iostream>
#include "Globals.h"
#include "TileTypes.h"

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
				if (i > 5 && i < 10 && j < 5) {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::mountain));
				}
				else if (i > 0 && i < 4 && j < 5 && j > 1) {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::hill));
				}
				else {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY));
				}
			}
			else {
				tileRow.push_back(Tile(i * w + w * globals::tileOffsetMultX, j * h * globals::tileOffsetMultY));
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
		actors.push_back(Actor(i * w, 0));
	}
}


void GameState::update(int elapsed)
{
	for (auto& actor : actors) {
		actor.update(elapsed);
	}
}
