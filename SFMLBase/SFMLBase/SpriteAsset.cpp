#include "SpriteAsset.h"
#include "GameManager.h"


void SpriteAsset::Setup(xml_node<>* spriteNode, string assetPath)
{
	texture.loadFromFile(assetPath + spriteNode->value());
	sprite.setTexture(texture);
	sprite.setColor(Color(255, 255, 255, 255));
}

void SpriteAsset::Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale)
{
	sprite.setPosition(pos);
	sprite.setScale(scale);
	window.draw(sprite);
}

SpriteAsset::SpriteAsset()
{
}


SpriteAsset::~SpriteAsset()
{
}
