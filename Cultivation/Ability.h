#pragma once

#include "AbilityEffect.h"

class Ability
{
public:
	Ability(bool targeted, int cooldown, int windup, int range, AbilityEffect* effect);
	~Ability();

	void execute(Vec2d targetIndex, std::vector<Actor>& actors, std::vector<Building>& buildings);

	bool targeted;
	int cooldown;
	int windup;
	int range;

	// move this into a hashmap later & access it through a key
	AbilityEffect* effect;
};

