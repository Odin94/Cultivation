#include "stdafx.h"
#include "ResourceManager.h"

void ResourceManager::loadTexturesAndSprites() {
	std::string filenames[] = { "SelectionCircle", "Hexagon", "MountainHexagon", "WaterHexagon", "HillHexagon", "HexagonHighlighted", "Actor", "SelectedActor", "Building" };

	for (auto& name : filenames) {
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

ResourceManager::ResourceManager()
{
}
