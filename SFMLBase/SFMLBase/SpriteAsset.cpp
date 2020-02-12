#include "SpriteAsset.h"
#include "GameManager.h"


void SpriteAsset::Setup(xml_node<>* spriteNode, string assetPath)
{
	texture.loadFromFile(assetPath + spriteNode->value());
	sprite;
	sprite.setTexture(texture);
	sprite.setColor(Color(255, 255, 255, 255));
}

SpriteAsset::SpriteAsset()
{
}


SpriteAsset::~SpriteAsset()
{
}
