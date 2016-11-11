#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadTextures();
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTextures()
{
	std::string filenames[] = { "Hexagon", "Actor" };

	for (const auto& name : filenames) {
		sf::Texture texture;
		if (!texture.loadFromFile("res/" + name + ".png"))
		{
			std::cout << "couldn't load texture! " << name;
		}

		texture.setSmooth(true);

		textures[name] = texture;
	}
}

sf::Sprite ResourceManager::loadSprite(std::string name) {
	sf::Sprite sprite;
	sprite.setTexture(textures[name]);

	return sprite;
}
