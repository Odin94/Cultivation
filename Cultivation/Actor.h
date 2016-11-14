#pragma once
#include "Tile.h"

class Actor
{
public:
	Actor(double x, double y);
	~Actor();

	double x, y, targetX, targetY, velX, velY;
	int w, h;

	// this should move to a Tile, really..
	void moveTo(Tile* tile) {
		this->targetX = tile->x;
		this->targetY = tile->y;


	}
};

