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
	if (attr != NULL) duration = atof(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "offset");
	if (attr != NULL) offset = atoi(attr->value());
	nextFrameChange = duration * 1000 / (amount) ;
	currentFrame = 0;
	columns = (float)texture.getSize().x / width;
	sprite.setTexture(texture);
	sprite.setOrigin(Vector2f(width / 2.0, height / 2.0));
}

//creates the Animation depending on the currentTime
void AnimationAsset::Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale)
{
	int currentTime = MyTime::clock->getElapsedTime().asMilliseconds();
	//frame change only needs to be called every other frame
	if (nextFrameChange - currentTime <= 0) {
		//small fix if the animation is paused and needs to catch up after not beeing used for some time since the SFML clock can't be paused
		while(nextFrameChange - currentTime <= 0)
			nextFrameChange += duration * 1000 / (amount);
		currentFrame++;
		currentFrame %= amount;
		int x = (offset + currentFrame) % columns;	//calculate position of frame inside of the texture
		int y = (offset + currentFrame) / columns;
		IntRect rect(x * width, y*height,width,height);
		sprite.setTextureRect(rect);
		sprite.setColor(Color(255, 255, 255, 255));
	}
	//these parameters need to be set every frame in case it got changed
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
