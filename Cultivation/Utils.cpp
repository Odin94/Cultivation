#include "stdafx.h"
#include "Utils.h"
#include <limits>
#include <algorithm>
#include <set>
#include <unordered_set>

namespace utils {
	bool isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2)
	{
		return !(x1 > x2 + w2 || x1 < x2 || y1 > y2 + h2 || y1 < y2);
	}

	int getHexDistance(Vec2d v1, Vec2d v2) {
		int x1 = v1.x - floor(v1.y / 2);
		int y1 = v1.y;
		int x2 = v2.x - floor(v2.y / 2);
		int y2 = v2.y;
		int dx = x2 - x1;
		int dy = y2 - y1;
		int maxDist = std::max(abs(dx), abs(dy));
		return std::max(maxDist, abs(dx + dy));
	}

	class Node {
	public:
		Node(Tile& tile, int distance) : tile(tile), distanceToEndPoint(distance) {}

		Tile& tile;
		int distanceToEndPoint;
		int costToReachFromStart = std::numeric_limits<int>::max();
		int totalDistance = std::numeric_limits<int>::max();

		Node* cameFrom = nullptr;

		void updateDistance(int costToReachFromStart) {
			this->costToReachFromStart = costToReachFromStart + tile.getCost();
			totalDistance = this->costToReachFromStart + distanceToEndPoint;
		}

		Vec2d getIndex() {
			return tile.getIndex();
		}

		bool operator<(const Node& other) {
			return distanceToEndPoint < other.distanceToEndPoint;
		}
		bool operator>(const Node& other) {
			return distanceToEndPoint > other.distanceToEndPoint;
		}
	};

	// TODO: make more efficient by declaring vector size before filling it..?
	std::vector<std::vector<Node>> getNodeMap(std::vector<std::vector<Tile>>& map, Vec2d startPoint, Vec2d endPoint) {
		std::vector<std::vector<Node>> nodeMap;
		for (int i = 0; i < map.size(); i++) {
			std::vector<Node> nodes;
			for (int j = 0; j < map[i].size(); j++) {
				nodes.push_back(Node(map[i][j], getHexDistance(endPoint, (Vec2d(i, j)))));
			}
			nodeMap.push_back(nodes);
		}

		nodeMap[startPoint.x][startPoint.y].updateDistance(0);

		return nodeMap;
	}

	std::deque<Tile*> reconstructPath(Node* node) {
		std::deque<Tile*> path;

		while (node->cameFrom != nullptr) {
			path.push_front(&node->tile);
			node = node->cameFrom;
		}

		return path;
	}

	Node* popEntryWithClosestTotalDistance(std::set<Node*>& nodes) {
		Node* closestNode;
		int minDist = std::numeric_limits<int>::max();
		for (auto node : nodes) {
			if (node->totalDistance < minDist) {
				minDist = node->totalDistance;
				closestNode = node;
			}
		}

		nodes.erase(closestNode);
		return closestNode;
	}


	std::deque<Tile*> findPath(Vec2d startPoint, Vec2d endPoint, std::vector<std::vector<Tile>>& map)
	{

		std::set<Node*> nodesToExplore;
		std::unordered_set<Vec2d> exploredNodes;


		auto nodeMap = getNodeMap(map, startPoint, endPoint);

		nodesToExplore.insert(&nodeMap[startPoint.x][startPoint.y]);

		while (!nodesToExplore.empty()) {
			Node* currentNode = popEntryWithClosestTotalDistance(nodesToExplore);

			// if currentNode is goal
			Vec2d currentIndex = currentNode->getIndex();
			if (currentNode->getIndex() == endPoint) return reconstructPath(currentNode);

			exploredNodes.insert(currentNode->getIndex());

			for (auto neighbour : currentNode->tile.neighbours) {
				Vec2d neighbourPos = neighbour->getIndex();

				// if neighbour in explored Nodes
				if (exploredNodes.find(neighbourPos) != exploredNodes.end()) {
					continue;
				}

				Node& neighbourNode = nodeMap[neighbourPos.x][neighbourPos.y];

				// Automatically checks if neighbourNode is in nodesToExplore because it's a set
				nodesToExplore.insert(&neighbourNode);

				int costFromThisPathPlusDistance = currentNode->costToReachFromStart + neighbourNode.tile.getCost();
				// if this path to neighbour is closer than any previous path, update
				if (costFromThisPathPlusDistance < neighbourNode.totalDistance) {
					neighbourNode.updateDistance(currentNode->totalDistance);
					neighbourNode.cameFrom = currentNode;
				};
			}
		}

		// no path found
		std::cout << "no path found!";
		std::deque<Tile*> emptyTiles;
		return emptyTiles;
	}
}