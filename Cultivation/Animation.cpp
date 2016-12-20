#include "stdafx.h"
#include "Animation.h"


Animation::Animation(std::string spriteName, int totalFrames, int frameWidth, int frameHeight, int frameDelay) : spriteName(spriteName), totalFrames(totalFrames), frameWidth(frameWidth), frameHeight(frameHeight), frameDelay(frameDelay)
{
}

Animation::~Animation()
{
}

void Animation::update(int elapsed)
{
	if (paused) return;

	delayAccumulator += elapsed;
	if (delayAccumulator >= frameDelay) {
		delayAccumulator = 0; // or should this be -= frameDelay?
		currentFrame++;
		currentFrame %= totalFrames;
	}
}

void Animation::draw(sf::Sprite* sprite, sf::RenderWindow* window, sf::Vector2f pos) {
	sprite->setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
	sprite->setPosition(pos);
	window->draw(*sprite);
}

void Animation::reset()
{
	delayAccumulator = 0;
	currentFrame = 0;
}

void Animation::pause()
{
	paused = true;
}

void Animation::resume()
{
	paused = false;
}
