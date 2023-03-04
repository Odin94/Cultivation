#pragma once
#include <map> // TODO: replace with unordered_map and provide std::hash for enum class Type for better performance (probably no noticeable difference though)

// TODO: load all this from a datafile?
namespace TileTypes
{
	enum class Type
	{
		hill,
		mountain,
		plains,
		water
	};

	const std::map<Type, int> costs = {{Type::plains, 1}, {Type::hill, 2}, {Type::mountain, 3}, {Type::water, 3}};
	const std::map<Type, bool> passable = {{Type::plains, true}, {Type::hill, true}, {Type::mountain, false}, {Type::water, false}};
	const std::map<Type, std::string> spriteNames = {{Type::plains, "Hexagon"}, {Type::hill, "HillHexagon"}, {Type::mountain, "MountainHexagon"}, {Type::water, "WaterHexagon"}};
}
