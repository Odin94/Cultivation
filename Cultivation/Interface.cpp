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
	handleMouse();
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

void Interface::handleMouse()
{
	if (LMBReleased()) {
		for (auto& actor : gamestate->actors) {
			if (isMouseOver(actor)) {
				selectedActor = &actor;
				break;
			}
		}
	}

	if (RMBReleased()) {
		if (selectedActor != nullptr) {
			for (auto& tileColumn : gamestate->tiles) {
				for (auto& tile : tileColumn) {
					if (isMouseOver(tile)) {
						selectedActor->moveTo(tile);
						break;
					}
				}
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && MMBwasPressedLastFrame) {
		Vec2d mousePosCurrentFrame = Vec2d(sf::Mouse::getPosition(*window));

		Vec2d mouseOffset = mousePosLastFrame - mousePosCurrentFrame;
		camera.moveBy(mouseOffset.x, mouseOffset.y);
	}

	LMBwasPressedLastFrame = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	RMBwasPressedLastFrame = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	MMBwasPressedLastFrame = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
	mousePosLastFrame = Vec2d(sf::Mouse::getPosition(*window));
}

bool Interface::RMBReleased()
{
	return (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && RMBwasPressedLastFrame);
}

bool Interface::LMBReleased()
{
	return (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && LMBwasPressedLastFrame);
}


void Interface::draw()
{
	window->clear();

	for (const auto& tileColumn : gamestate->tiles) {
		for (const auto& tile : tileColumn) {
			drawAtWithCameraOffset(&resourceManager->sprites["Hexagon"], tile.pos.x, tile.pos.y);
		}
	}

	for (const auto& actor : gamestate->actors) {
		if (&actor == selectedActor) {
			drawAtWithCameraOffset(&resourceManager->sprites["SelectedActor"], actor.pos.x, actor.pos.y);
		}
		else {
			drawAtWithCameraOffset(&resourceManager->sprites["Actor"], actor.pos.x, actor.pos.y);
		}
	}

	window->display();
}

void Interface::drawAtWithCameraOffset(sf::Sprite* sprite, double x, double y)
{
	sprite->setPosition(sf::Vector2f(x - camera.offsetX, y - camera.offsetY));
	window->draw(*sprite);
}

bool Interface::isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2)
{
	return !(x1 > x2 + w2 || x1 < x2 || y1 > y2 + h2 || y1 < y2);
}

bool Interface::isMouseOver(Actor& actor)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return isPointOverRect(mousePos.x + camera.offsetX, mousePos.y + camera.offsetY, actor.pos.x, actor.pos.y, actor.w, actor.h);
}

bool Interface::isMouseOver(Tile& tile)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return isPointOverRect(mousePos.x + camera.offsetX, mousePos.y + camera.offsetY, tile.pos.x, tile.pos.y, tile.w, tile.h);
}


