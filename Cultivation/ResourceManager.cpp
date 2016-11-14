#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadTexturesAndSprites();
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTexturesAndSprites()
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

		sf::Sprite sprite;
		sprite.setTexture(textures[name]);
		sprites[name] = sprite;
	}
}
