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
	void handleMouse();
	void draw();

private:
	Camera camera;
	sf::RenderWindow* window;
	GameState* gamestate;
	ResourceManager* resourceManager;

	Actor* selectedActor = nullptr;

	void drawAtWithCameraOffset(sf::Sprite* sprite, double x, double y);

	bool isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2); // TODO: move this to somewhere more appropriate (utils class? Mouse Wrapper?)
	bool isMouseOver(Actor& actor);
	bool isMouseOver(Tile& tile);
};

