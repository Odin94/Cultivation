#pragma once
#include "Tile.h"
#include <vector>
#include "Vec2d.h"

namespace utils {
	std::vector<Tile*> findPath(Vec2d startPoint, Vec2d endPoint, std::vector<std::vector<Tile>>& map);
}