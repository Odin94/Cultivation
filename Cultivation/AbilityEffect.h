#pragma once

#include "Vec2d.h"
#include <memory>

class Actor;
class Building;

class AbilityEffect
{
public:
	AbilityEffect();
	~AbilityEffect();

	virtual void execute(Vec2d target, std::vector<Actor>& actors, std::vector<Building>& buildings) = 0;
};
