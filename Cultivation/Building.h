#pragma once
#include "GameObject.h"

class Building : public GameObject
{
public:
    Building(double x, double y, std::string animIdleSpriteName, Ability *firstAbility = nullptr, int team = 1);
    ~Building();

    void RMBAction(GameObject &object) override;
    void updateAnimation(int elapsed) override;
};
