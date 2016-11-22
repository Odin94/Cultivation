#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Vec2d.h"


class Interface
{
public:
	Interface(sf::RenderWindow* window, GameState* gamestate, ResourceManager* resourceManager);
	~Interface();

	void update(int elapsed);
	void handleKeyboard(int elapsed);
	void handleMouse();
	bool RMBReleased();
	bool LMBReleased();
	void draw();

private:
	Camera camera;
	sf::RenderWindow* window;
	GameState* gamestate;
	ResourceManager* resourceManager;

	Actor* selectedActor = nullptr;

	bool LMBwasPressedLastFrame = false;
	bool RMBwasPressedLastFrame = false;
	bool MMBwasPressedLastFrame = false;
	Vec2d mousePosLastFrame = Vec2d(0, 0);
	
	void drawAtWithCameraOffset(sf::Sprite* sprite, double x, double y);

	bool isPointOverRect(int x1, int y1, int x2, int y2, int w2, int h2); // TODO: move this to somewhere more appropriate (utils class? Mouse Wrapper?)
	bool isMouseOver(Actor& actor);
	bool isMouseOver(Tile& tile);
};

