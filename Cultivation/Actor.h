#pragma once
#include "Tile.h"
#include "Vec2d.h"
#include "Animation.h"
#include <deque>


class Actor
{
public:
	Actor(double x, double y, std::string animRunningSpriteName);
	~Actor();

	Animation anim;

	Vec2d pos, tar;
	double speed = 0.4;
	int w, h;

	std::deque<Tile*> tarPath;

	void findPathAndMoveTo(Tile& tile);
	void moveTo(Tile& tile);
	void update(int elapsed);
	void draw(sf::Sprite* sprite, sf::RenderWindow* window, sf::Vector2f drawPos);
	Vec2d getIndex();

};

