#include "Building.h"
#include "Globals.h"

Building::Building(double x, double y, std::string animIdleSpriteName, Ability *firstAbility, int team) : GameObject(x, y, globals::actorWidth, globals::actorHeight, Animation(animIdleSpriteName, 1, globals::actorWidth, globals::actorHeight), std::move(firstAbility), team)
{
}

Building::~Building() {}

void Building::RMBAction(GameObject &object)
{
}

void Building::updateAnimation(int elapsed)
{
}
