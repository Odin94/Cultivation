#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::string spriteName, int totalFrames, int frameWidth, int frameHeight, int frameDelay = 100);
	~Animation();

	std::string spriteName;

	void update(int elapsed);
	void draw(sf::Sprite* sprite, sf::RenderWindow* window, sf::Vector2f pos);
	void reset();
	void pause();
	void resume();

private:
	const int totalFrames, frameDelay, frameWidth, frameHeight;
	int delayAccumulator = 0, currentFrame = 0;
	bool paused = false;
};

