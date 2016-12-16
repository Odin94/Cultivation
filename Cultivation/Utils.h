#pragma once
#include "Tile.h"
#include <vector>
#include "Vec2d.h"
#include <deque>

namespace utils {
	bool isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2);
	bool isPointOverCircle(int x1, int y1, int x2, int y2, int r);
	std::deque<Tile*> findPath(Vec2d startPoint, Vec2d endPoint, std::vector<std::vector<Tile>>& map);
}