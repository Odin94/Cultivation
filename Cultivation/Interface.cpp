#include "stdafx.h"
#include "Interface.h"
#include "Globals.h"
#include "Utils.h"
#include "TileTypes.h"

// KEEP IN MIND: If actors/buildings gets reallocated, selectedObject* is no longer valid!!


Interface::Interface(sf::RenderWindow* window) : window(window) {}
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

	//Abilities
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (selectedObject) {
			selectedAbility = selectedObject->firstAbility;
		}
	}
}


void Interface::handleMouse() {
	if (LMBReleased()) {

		// casting an ability
		if (selectedAbility) {
			Vec2d targetIndex = getMousePosIndex();

			if (selectedAbility->range >= utils::getHexDistance(selectedObject->getIndex(), targetIndex)) {
				std::cout << targetIndex;
				std::cout << sf::Mouse::getPosition(*window) << "\n";
				selectedAbility->execute(targetIndex, gamestate.actors, gamestate.buildings);
				selectedAbility = nullptr;
			}
			else {
				// target out of range, play an error sound or something?
			}
		}

		// not casting an ability, select things
		else {
			for (auto& actor : gamestate.actors) {
				if (isMouseOver(actor)) {
					selectedObject = &actor;
					break;
				}
			}
			for (auto& building : gamestate.buildings) {
				if (isMouseOver(building)) {
					selectedObject = &building;
					break;
				}
			}
		}
	}

	// TODO: calculate tile from mouse-pos instead of checking for every tile for improved efficiency if necessary
	if (RMBReleased()) {
		selectedAbility = nullptr;

		if (selectedObject != nullptr) {
			for (auto& tileColumn : gamestate.tiles) {
				for (auto& tile : tileColumn) {
					if (isMouseOver(tile)) {
						selectedObject->RMBAction(tile);
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

	for (auto& tileColumn : gamestate.tiles) {
		for (auto& tile : tileColumn) {
			tile.draw(window, sf::Vector2f(tile.pos.x - camera.offset.x, tile.pos.y - camera.offset.y));
			if (tile.highlighted) drawAtWithCameraOffset(ResourceManager::getInstance().sprites["HexagonHighlighted"], tile.pos.x, tile.pos.y);
		}
	}

	for (auto& actor : gamestate.actors) {
		actor.draw(window, sf::Vector2f(actor.pos.x - camera.offset.x, actor.pos.y - camera.offset.y));
		if (&actor == selectedObject) {
			drawAtWithCameraOffset(ResourceManager::getInstance().sprites["SelectionCircle"], actor.pos.x, actor.pos.y);
		}
	}

	for (auto& building : gamestate.buildings) {
		building.draw(window, sf::Vector2f(building.pos.x - camera.offset.x, building.pos.y - camera.offset.y));
		if (&building == selectedObject) {
			drawAtWithCameraOffset(ResourceManager::getInstance().sprites["SelectionCircle"], building.pos.x, building.pos.y);
		}
	}

	window->display();
}


void Interface::drawAtWithCameraOffset(sf::Sprite& sprite, double x, double y)
{
	sprite.setPosition(sf::Vector2f(x - camera.offset.x, y - camera.offset.y));
	window->draw(sprite);
}



bool Interface::isMouseOver(GameObject& obj)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return utils::isPointOverCircle(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, obj.pos.x + obj.w / 2, obj.pos.y + obj.h / 2, obj.w / 2);
}

Vec2d Interface::getMousePosIndex() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	return utils::getAccurateIndex(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y, gamestate.tiles);//utils::getIndex(mousePos.x + camera.offset.x, mousePos.y + camera.offset.y);
}



