#include "stdafx.h"
#include "Actor.h"
#include "Globals.h"
#include "Utils.h"
#include "GameState.h"

Actor::Actor(double x, double y, std::string animIdleSpriteName, std::string animRunningSpriteName): GameObject(x, y, globals::actorWidth, globals::actorHeight, Animation(animIdleSpriteName, 1, globals::actorWidth, globals::actorHeight)), tar(Vec2d(x, y)) {
	animations.emplace(std::make_pair(AnimationType::moving, Animation(animRunningSpriteName, 3, w, h)));
}
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

	updateAnimation(elapsed);
}

void Actor::updateAnimation(int elapsed)
{
	// if not moving and not in idle anim, reset current anim and set anim to idle
	if (currentAnim != &animations.at(AnimationType::idle) && pos == tar && tarPath.empty()) {
		currentAnim->reset();
		currentAnim = &animations.at(AnimationType::idle);
	}
	// if moving and not in moving anim
	else if (currentAnim != &animations.at(AnimationType::moving)) {
		currentAnim->reset();
		currentAnim = &animations.at(AnimationType::moving);
	}
	
	currentAnim->update(elapsed);
}


