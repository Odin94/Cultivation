#pragma once
#include "Ability.h"
#include "Animation.h"
#include <deque>
#include <memory>
#include <vector>

class GameObject
{
public:
    GameObject(int x, int y, int w, int h, Animation animation, Ability *firstAbility, int team = 1);
    ~GameObject();

    virtual void RMBAction(GameObject &obj);
    virtual void updateAnimation(int elapsed);
    void draw(sf::RenderWindow *window, sf::Vector2f pos);
    Vec2d getIndex();

    Vec2d pos;
    int x, y, w, h;

    int team;

    std::map<AnimationType, Animation> animations;
    AnimationType currentAnim;

    Ability *firstAbility;
};
