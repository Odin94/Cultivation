#include "stdafx.h"
#include "Interface.h"
#include "Globals.h"
#include "Utils.h"
#include "TileTypes.h"


Interface::Interface(sf::RenderWindow* window, ResourceManager* resourceManager) : window(window), resourceManager(resourceManager) {}
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

	// TODO: calculate tile from mouse-pos instead of checking for every tile for improved efficiency if necessary
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
				tile.highlighted = false;
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
			std::string spriteName = TileTypes::spriteNames.at(tile.type);
			drawAtWithCameraOffset(&resourceManager->sprites[spriteName], tile.pos.x, tile.pos.y);
			if (tile.highlighted) drawAtWithCameraOffset(&resourceManager->sprites["HexagonHighlighted"], tile.pos.x, tile.pos.y);
		}
	}

	for (auto& actor : gamestate.actors) {
		if (&actor == selectedActor) {
			actor.draw(&resourceManager->sprites["SelectedActor"], window, sf::Vector2f(actor.pos.x - camera.offset.x, actor.pos.y - camera.offset.y));
		}
		else {
			actor.draw(&resourceManager->sprites["Actor"], window, sf::Vector2f(actor.pos.x - camera.offset.x, actor.pos.y - camera.offset.y));
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
	return utils::isPointOverCircle(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, actor.pos.x + actor.w / 2, actor.pos.y + actor.h / 2, actor.w / 2);
}


bool Interface::isMouseOver(Tile& tile)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return utils::isPointOverCircle(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, tile.pos.x + tile.w/2, tile.pos.y + tile.h/2, tile.w / 2); // assumes tile.w == tile.h
}


