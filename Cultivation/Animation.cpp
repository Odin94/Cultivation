#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"


Animation::Animation(std::string spriteName, int totalFrames, int frameWidth, int frameHeight, int frameDelay) : sprite(ResourceManager::getInstance().sprites.at(spriteName)), totalFrames(totalFrames), frameWidth(frameWidth), frameHeight(frameHeight), frameDelay(frameDelay), spriteName(spriteName) {}
Animation::~Animation() {}


void Animation::update(int elapsed)
{
	if (paused || totalFrames == 1) return;

	delayAccumulator += elapsed;
	if (delayAccumulator >= frameDelay) {
		delayAccumulator = 0; // or should this be -= frameDelay instead of resetting?
		currentFrame++;
		currentFrame %= totalFrames;
	}
}

void Animation::draw(sf::RenderWindow* window, sf::Vector2f pos) {
	sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
	sprite.setPosition(pos);
	window->draw(sprite);
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

std::ostream& operator<<(std::ostream &strm, const Animation &anim) {
	return strm << "Animation(sprName: " << anim.spriteName << "\n";
}