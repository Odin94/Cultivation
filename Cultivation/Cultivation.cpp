// Cultivation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Actor.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>

std::vector<std::vector<Tile>> tiles;
std::vector<Actor> actors;


void drawAt(sf::RenderWindow* window, sf::Sprite* sprite, int x, int y) {
	sprite->setPosition(sf::Vector2f(x, y));
	window->draw(*sprite);
}

void run() {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Cultivation");

	GameState& gamestate = GameState::getInstance();
	ResourceManager resourceManager; // must be called after RenderWindow I guess.. or at least not from a global thingy
	Interface interface(&window, &resourceManager);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsedTime = clock.restart();
		int elapsed = elapsedTime.asMilliseconds();
		if (elapsed > 20) {
			elapsed = 20;
		}

		gamestate.update(elapsed);
		interface.update(elapsed);
		interface.draw();
	}
}

int main()
{
	run();
	return 0;
}