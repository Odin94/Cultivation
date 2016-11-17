#include "stdafx.h"
#include "Actor.h"

// TODO: Don't hardcode width/height values
Actor::Actor(double x, double y) : pos(Vec2d(x, y)), w(128), h(128), tar(Vec2d(x, y)) {}


Actor::~Actor() {}

void Actor::moveTo(Tile& tile)
{
	tar = Vec2d(tile.x, tile.y);
}

void Actor::update(int elapsed)
{
	if ((pos != tar)) {
		Vec2d vel = tar - pos;
		vel.setLength(speed * elapsed);

		pos += vel;

		double postardist = pos.getDistance(tar);
		double velLen = vel.getLength();
		if (pos.getDistance(tar) < vel.getLength()) {
			pos = tar;
		}
	}
}