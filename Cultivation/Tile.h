#pragma once

class Actor;

class Tile
{
public:
	Tile(int x, int y, int w = 64, int h = 64);
	~Tile();

	int x, y, w, h;
	Actor* occupyingActor;

};

