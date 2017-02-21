#pragma once
#include "Tile.h"
#include <vector>
#include "Vec2d.h"
#include <deque>

namespace utils {
	bool isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2);
	bool isPointOverCircle(int x1, int y1, int x2, int y2, int r);
	std::deque<Tile*> findPath(Vec2d startPoint, Vec2d endPoint, std::vector<std::vector<Tile>>& map);

	int getHexDistance(Vec2d v1, Vec2d v2);
	int getHexDistanceIndex(Vec2d v1, Vec2d v2);
	
	Vec2d getApproximateIndex(Vec2d pos);
	Vec2d getApproximateIndex(double x, double y);
	
	Vec2d indexToPixels(Vec2d index);

	Vec2d getAccurateIndex(Vec2d pos, std::vector<std::vector<Tile>>& map);
	Vec2d getAccurateIndex(double x, double y, std::vector<std::vector<Tile>>& map);
}