#include "stdafx.h"
#include "Actor.h"


Actor::Actor(double x, double y) : x(x), y(y), targetX(x), targetY(y), velX(0), velY(0) {}


Actor::~Actor() {}
