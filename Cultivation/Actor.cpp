#include "stdafx.h"
#include "Actor.h"
#include "Globals.h"
#include "Utils.h"
#include "GameState.h"

Actor::Actor(double x, double y, std::string animIdleSpriteName, std::string animRunningSpriteName, Ability* firstAbility): GameObject(x, y, globals::actorWidth, globals::actorHeight, Animation(animIdleSpriteName, 1, globals::actorWidth, globals::actorHeight), std::move(firstAbility)), tar(Vec2d(x, y)) {
	animations.emplace(std::make_pair(AnimationType::moving, Animation(animRunningSpriteName, 3, w, h)));
}
Actor::~Actor() {}

void Actor::RMBAction(GameObject& object)
{
	findPathAndMoveTo(object);
}

void Actor::findPathAndMoveTo(GameObject& object)
{
	tarPath = utils::findPath(getIndex(), object.getIndex(), GameState::getInstance().tiles);
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
	if (currentAnim != AnimationType::idle && pos == tar && tarPath.empty()) {
		animations.at(currentAnim).reset();
		currentAnim = AnimationType::idle;
	}
	// if moving and not in moving anim
	else if (currentAnim != AnimationType::moving) {
		animations.at(currentAnim).reset();
		currentAnim = AnimationType::moving;
	}
	
	animations.at(currentAnim).update(elapsed);
}


