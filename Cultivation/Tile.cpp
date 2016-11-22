#include "stdafx.h"
#include "Tile.h"
#include "Globals.h"


Tile::Tile(int x, int y) : pos(Vec2d(x, y)), w(globals::tileWidth), h(globals::tileHeight) {}


Tile::~Tile() {}
