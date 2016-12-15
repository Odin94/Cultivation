#include "stdafx.h"
#include "Interface.h"
#include "Globals.h"
#include "Utils.h"

Interface::Interface(sf::RenderWindow* window, ResourceManager* resourceManager) : window(window), resourceManager(resourceManager)
{
}


Interface::~Interface() {}

void Interface::update(int elapsed)
{
	handleKeyboard(elapsed);
	handleMouse();

	camera.update(elapsed);
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

void Interface::handleMouse() {
	if (LMBReleased()) {
		for (auto& actor : gamestate.actors) {
			if (isMouseOver(actor)) {
				selectedActor = &actor;
				break;
			}
		}
	}

	if (RMBReleased()) {
		if (selectedActor != nullptr) {
			for (auto& tileColumn : gamestate.tiles) {
				for (auto& tile : tileColumn) {
					if (isMouseOver(tile)) {
						selectedActor->findPathAndMoveTo(tile);
						break;
					}
				}
			}
		}
		for (auto& tileColumn : gamestate.tiles) {
			for (auto& tile : tileColumn) {
				for (auto neighbour : tile.neighbours) {
					neighbour->highlighted = false;
				}
			}
		}
		for (auto& tileColumn : gamestate.tiles) {
			for (auto& tile : tileColumn) {
				if (isMouseOver(tile)) {
					std::cout << tile.getIndex() << "\n";
					for (auto neighbour : tile.neighbours) {
						neighbour->highlighted = true;
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

	for (const auto& tileColumn : gamestate.tiles) {
		for (const auto& tile : tileColumn) {
			if (tile.highlighted) {
				drawAtWithCameraOffset(&resourceManager->sprites["HexagonHighlighted"], tile.pos.x, tile.pos.y);
			}
			else {
				drawAtWithCameraOffset(&resourceManager->sprites["Hexagon"], tile.pos.x, tile.pos.y);
			}
		}
	}

	for (const auto& actor : gamestate.actors) {
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
	sprite->setPosition(sf::Vector2f(x - camera.offset.x, y - camera.offset.y));
	window->draw(*sprite);
}



bool Interface::isMouseOver(Actor& actor)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return utils::isPointOverRect(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, actor.pos.x, actor.pos.y, actor.w, actor.h);
}

bool Interface::isMouseOver(Tile& tile)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return utils::isPointOverRect(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, tile.pos.x, tile.pos.y, tile.w, tile.h);
}


