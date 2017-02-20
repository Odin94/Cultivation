#pragma once
#include "Tile.h"
#include "GameObject.h"
#include <deque>
#include <memory>


class Actor: public GameObject
{
public:
	Actor(double x, double y, std::string animIdleSpriteName, std::string animRunningSpriteName, Ability* firstAbility = nullptr);
	~Actor();

	Vec2d tar;
	double speed = 0.4;
	

	std::deque<Tile*> tarPath;

	void RMBAction(GameObject& object) override;

	void findPathAndMoveTo(GameObject& object);
	void moveTo(Tile& tile);
	void update(int elapsed);

	void updateAnimation(int elapsed) override;
};

