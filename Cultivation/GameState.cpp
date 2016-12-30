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
			if (j % 2 == 0) {  // i = 2: all not set, 1: set, 0: set, 3: set, 4: set, 5 set, 16: set
				if (i > 5 && i < 10 && j < 5) {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::mountain, 1)); // type here determines right anims
				}
				else if (i > 0 && i < 4 && j < 5 && j > 1) {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::hill, 1));
				}

				else if (i > 0 && i < 8 && j > 5 && j < 12) {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::water, 4));
				}
				else {
					tileRow.push_back(Tile(i * w, j * h * globals::tileOffsetMultY, TileTypes::Type::plains, 1)); // type here determines all other anims
				}
			}
			else {
				tileRow.push_back(Tile(i * w + w * globals::tileOffsetMultX, j * h * globals::tileOffsetMultY, TileTypes::Type::plains, 1));
			}
		}
		tiles.push_back(tileRow);
	}

	for (auto& tileRow : tiles) {
		for (auto& tile : tileRow) {
			tile.findNeighbours(tiles);
			tile.currentAnim = &tile.animations.at(AnimationType::idle);  // if we don't do this tile animations are set to "Hexagon" in cases where Hexagon isn't even in their animations map :x
		}
	}

	// create some actors
	for (int i = 0; i < 5; i++) {
		actors.push_back(Actor(i * w, 0, "Actor", "Actor"));
	}

	// create a building
	buildings.push_back(Building(2 * w, 1 * h * globals::tileOffsetMultY, "Building"));

	for (auto& building : buildings) {
		building.currentAnim = &building.animations.at(AnimationType::idle);
	}
}


void GameState::update(int elapsed)
{
	for (auto& column : tiles) {
		for (auto& tile : column) {
			tile.occupyingObject = nullptr;
			tile.updateAnimation(elapsed);
		}
	}

	for (auto& building : buildings) {
		tiles[building.getIndex().x][building.getIndex().y].occupyingObject = &building;
	}

	for (auto& actor : actors) {
		actor.update(elapsed);
		tiles[actor.getIndex().x][actor.getIndex().y].occupyingObject = &actor;
	}
}
