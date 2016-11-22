#include "stdafx.h"
#include "Actor.h"
#include "Globals.h"

Actor::Actor(double x, double y) : pos(Vec2d(x, y)), w(globals::actorWidth), h(globals::actorHeight), tar(Vec2d(x, y)) {}


Actor::~Actor() {}

void Actor::moveTo(Tile& tile)
{
	tar = tile.pos;
}

void Actor::update(int elapsed)
{
	if ((pos != tar)) {
		Vec2d vel = tar - pos;
		vel.setLength(speed * elapsed);

		pos += vel;

		if (pos.getDistance(tar) < vel.getLength()) {
			pos = tar;
		}
	}
}