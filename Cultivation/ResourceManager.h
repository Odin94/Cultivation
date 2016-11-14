#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Sprite> sprites;

	void loadTexturesAndSprites();
};

