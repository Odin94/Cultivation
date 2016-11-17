#pragma once

class Actor;

class Tile
{
public:
	Tile(int x, int y, int w = 128, int h = 128); // TODO: put width and height of tiles and actors (and other thingies) somewhere in one single place
	~Tile();

	int x, y, w, h; // TODO: use Vec2d instead of two ints
	Actor* occupyingActor;

};

