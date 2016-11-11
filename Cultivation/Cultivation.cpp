// Cultivation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Actor.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>


std::vector<std::vector<Tile>> tiles;
std::vector<Actor> actors;


void drawAt(sf::RenderWindow* window, sf::Sprite* sprite, int x, int y) {
	sprite->setPosition(sf::Vector2f(x, y));
	window->draw(*sprite);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	ResourceManager resourceManager; // must be called after RenderWindow I guess.. or at least not from a global thingy

	// fill 2 dimensional vector with tiles
	int w = 128;
	int h = 128;
	for (int i = 0; i < 20; i++) {
		std::vector<Tile> tileRow;
		for (int j = 0; j < 20; j++) {
			if (j % 2 == 0) {
				tileRow.push_back(Tile(i * w, j * h * 0.75));
			}
			else {
				tileRow.push_back(Tile(i * w + w * 0.5, j * h * 0.75));
			}
		}
		tiles.push_back(tileRow);
	}

	// create some actors
	for (int i = 0; i < 5; i++) {
		actors.push_back(Actor(i * 128, 0));
	}

	sf::Sprite hexagonSprite = resourceManager.loadSprite("Hexagon");
	sf::Sprite actorSprite = resourceManager.loadSprite("Actor");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (const auto& tileColumn : tiles) {
			for (const auto& tile : tileColumn) {
				drawAt(&window, &hexagonSprite, tile.x, tile.y);
			}
		}

		for (const auto& actor : actors) {
			drawAt(&window, &actorSprite, actor.x, actor.y);
		}

		window.display();
	}

	return 0;
}