#pragma once
#include <SFML/Graphics.hpp>

enum class AnimationType
{
	idle,
	moving
};

class Animation
{
public:
	Animation(std::string spriteName, int totalFrames, int frameWidth, int frameHeight, int frameDelay = 100);
	~Animation();

	std::string spriteName;
	sf::Sprite &sprite;

	void update(int elapsed);
	void draw(sf::RenderWindow *window, sf::Vector2f pos);
	void reset();
	void pause();
	void resume();

private:
	const int totalFrames, frameDelay, frameWidth, frameHeight;
	int delayAccumulator = 0, currentFrame = 0;
	bool paused = false;
};

std::ostream &operator<<(std::ostream &strm, const Animation &anim);