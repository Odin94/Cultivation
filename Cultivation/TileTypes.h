#pragma once
#include <map> // TODO: replace with unordered_map and provide std::hash for enum class Type for better performance (probably no noticeable difference though)

namespace TileTypes {
	enum class Type;

	// std::map<Type, int> costs; // causes compile error
}
