#pragma once
#include "Tile.h"
#include "Ability.h"
#include "Animation.h"
#include <deque>
#include <memory>

class GameObject
{
public:
    GameObject(int x, int y, int w, int h, Animation animation, Ability *firstAbility, int team = 1);
    ~GameObject();

    virtual void RMBAction(GameObject &obj);
    Vec2d getIndex();

    Vec2d pos;
    int w;
    int h;
};
