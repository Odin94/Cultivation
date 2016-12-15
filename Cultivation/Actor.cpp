#include "stdafx.h"
#include "Actor.h"
#include "Globals.h"
#include "Utils.h"
#include "GameState.h"

Actor::Actor(double x, double y) : pos(Vec2d(x, y)), w(globals::actorWidth), h(globals::actorHeight), tar(Vec2d(x, y)) {}


Actor::~Actor() {}

void Actor::findPathAndMoveTo(Tile & tile)
{
	tarPath = utils::findPath(getIndex(), tile.getIndex(), GameState::getInstance().tiles);
}

void Actor::moveTo(Tile& tile)
{
	tar = tile.pos;
}

void Actor::update(int elapsed)
{
	if (pos == tar && !tarPath.empty()) {
		Tile* tarTile = tarPath.front();
		tarPath.pop_front();
		tar = Vec2d(tarTile->pos.x, tarTile->pos.y);
	}

	if ((pos != tar)) {
		Vec2d vel = tar - pos;
		vel.setLength(speed * elapsed);

		pos += vel;

		if (pos.getDistance(tar) < vel.getLength()) {
			pos = tar;
		}
	}
}

Vec2d Actor::getIndex()
{
	return Vec2d(int(pos.x / w), round(pos.y / h / globals::tileOffsetMultY));
}
