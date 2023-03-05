#include "GameObject.h"

GameObject::GameObject(int x, int y, int w, int h, Animation animation, Ability *firstAbility, int team) : x(x), y(y), w(w), h(h), firstAbility(firstAbility), team(team)
{
    animations.emplace(std::make_pair(AnimationType::idle, animation));
    currentAnim = AnimationType::idle;
}

GameObject::~GameObject() {}

void GameObject::RMBAction(GameObject &obj)
{
}

Vec2d GameObject::getIndex()
{
    return Vec2d(0, 0);
}

void GameObject::draw(sf::RenderWindow *window, sf::Vector2f pos)
{
    animations.at(currentAnim).draw(window, pos);
}

void GameObject::updateAnimation(int elapsed)
{
    animations.at(currentAnim).update(elapsed);
}