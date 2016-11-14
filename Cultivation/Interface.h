#pragma once
#include "Camera.h"
#include "GameState.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>



class Interface
{
public:
	Interface(sf::RenderWindow* window, GameState* gamestate, ResourceManager* resourceManager);
	~Interface();

	void update(int elapsed);
	void handleKeyboard(int elapsed);
	void draw();

private:
	Camera camera;
	sf::RenderWindow* window;
	GameState* gamestate;
	ResourceManager* resourceManager;

	void drawAtWithCameraOffset(sf::Sprite* sprite, double x, double y);
};

