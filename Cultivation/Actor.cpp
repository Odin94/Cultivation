#include "stdafx.h"
#include "Actor.h"

// TODO: Don't hardcode width/height values
Actor::Actor(double x, double y) : x(x), y(y), w(128), h(128), targetX(x), targetY(y), velX(0), velY(0) {}


Actor::~Actor() {}
