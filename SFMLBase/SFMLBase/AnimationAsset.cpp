#include "AnimationAsset.h"
#include "GameManager.h"
#include "MyTime.h"
using namespace std;
void AnimationAsset::Setup(xml_node<>* spriteNode, string assetPath)
{
	texture.loadFromFile(assetPath + spriteNode->value());
	xml_attribute<>* attr = GameManager::FindAttribute(spriteNode, "width");
	if (attr != NULL) width = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "height");
	if (attr != NULL) height = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "amount");
	if (attr != NULL) amount = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "duration");
	if (attr != NULL) duration = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "offset");
	if (attr != NULL) offset = atoi(attr->value());
	nextFrameChange = duration * 1000 / (amount) ;
	currentFrame = 0;
	columns = (float)texture.getSize().x / width;
	sprite.setTexture(texture);
}

void AnimationAsset::Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale)
{
	int currentTime = MyTime::clock->getElapsedTime().asMilliseconds();
	if (nextFrameChange - currentTime <= 0) {
		nextFrameChange += duration * 1000 / (amount);
		currentFrame++;
		currentFrame %= amount;
		int x = (offset + currentFrame) % columns;
		int y = (offset + currentFrame) / columns;
		IntRect rect(x * width, y*height,width,height);
		sprite.setTextureRect(rect);
		sprite.setColor(Color(255, 255, 255, 255));
	}
	sprite.setPosition(pos);
	sprite.setScale(scale);
	window.draw(sprite);
}

AnimationAsset::AnimationAsset()
{
}


AnimationAsset::~AnimationAsset()
{
}
