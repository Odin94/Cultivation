#include "stdafx.h"
#include "Actor.h"
#include "Globals.h"
#include "Utils.h"
#include "GameState.h"

Actor::Actor(double x, double y, std::string animRunningSpriteName) : pos(Vec2d(x, y)), w(globals::actorWidth), h(globals::actorHeight), tar(Vec2d(x, y)), anim(Animation(animRunningSpriteName, 3, globals::tileWidth, globals::tileHeight)) {}


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

	anim.update(elapsed);
}

void Actor::draw(sf::Sprite * sprite, sf::RenderWindow * window, sf::Vector2f drawPos)
{
	// if not moving
	if (pos == tar && tarPath.empty()) {
		anim.reset();
	}
	// if moving
	else {
	}
	anim.draw(sprite, window, drawPos);
}

Vec2d Actor::getIndex()
{
	return Vec2d(int(pos.x / w), round(pos.y / h / globals::tileOffsetMultY));
}
