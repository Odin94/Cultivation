#pragma once

#include "AbilityEffect.h"

class SpawnEffect : public AbilityEffect
{
public:
	SpawnEffect(Actor* actorToSpawn);
	~SpawnEffect();

	void execute(Vec2d targetIndex, std::vector<Actor>& actors, std::vector<Building>& buildings) override;

	Actor* actorToSpawn;
};

