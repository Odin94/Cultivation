#include "stdafx.h"
#include "Interface.h"


Interface::Interface(sf::RenderWindow* window, GameState* gamestate, ResourceManager* resourceManager) : window(window), gamestate(gamestate), resourceManager(resourceManager)
{
	Camera camera();
}


Interface::~Interface() {}

void Interface::update(int elapsed)
{
	handleKeyboard(elapsed);
}

void Interface::handleKeyboard(int elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera.moveBy(-camera.speed * elapsed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera.moveBy(camera.speed * elapsed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera.moveBy(0, -camera.speed * elapsed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera.moveBy(0, camera.speed * elapsed);
	}
}

void Interface::draw()
{
	window->clear();

	for (const auto& tileColumn : gamestate->tiles) {
		for (const auto& tile : tileColumn) {
			drawAtWithCameraOffset(&resourceManager->sprites["Hexagon"], tile.x, tile.y);
		}
	}

	for (const auto& actor : gamestate->actors) {
		drawAtWithCameraOffset(&resourceManager->sprites["Actor"], actor.x, actor.y);
	}

	window->display();
}

void Interface::drawAtWithCameraOffset(sf::Sprite* sprite, double x, double y)
{
	sprite->setPosition(sf::Vector2f(x - camera.offsetX, y - camera.offsetY));
	window->draw(*sprite);
}

