#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

// REFACTOR: maybe turn this into a namespace instead of a singleton?

// singleton
class ResourceManager
{
public:
	static ResourceManager& getInstance() {
		static ResourceManager instance; // instantiated on first use
		return instance;
	}

	void loadTexturesAndSprites();

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Sprite> sprites;

	// can't be copied or assigned
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;


private:
	ResourceManager();
};

