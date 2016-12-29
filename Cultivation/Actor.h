#pragma once
#include "Tile.h"
#include "GameObject.h"
#include <deque>


class Actor: public GameObject
{
public:
	Actor(double x, double y, std::string animIdleSpriteName, std::string animRunningSpriteName);
	~Actor();

	Vec2d tar;
	double speed = 0.4;
	

	std::deque<Tile*> tarPath;

	void findPathAndMoveTo(Tile& tile);
	void moveTo(Tile& tile);
	void update(int elapsed);

	void updateAnimation(int elapsed) override;
};

