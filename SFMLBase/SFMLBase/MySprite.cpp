#include "MySprite.h"
#include "GameManager.h"


void MySprite::Setup(xml_node<>* spriteNode, map<string, GameAsset*>& assets)
{
	sprite = (SpriteAsset*)assets[spriteNode->value()];
	xml_attribute<>* attr = GameManager::FindAttribute(spriteNode, "posx");
	if(attr != NULL)pos.x = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "posy");
	if (attr != NULL)pos.y = atoi(attr->value());
	
	attr = GameManager::FindAttribute(spriteNode, "sizex");
	if (attr != NULL)size.x = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "sizex");
	if (attr != NULL)size.x = atoi(attr->value());
}

void MySprite::Update(RenderWindow & window)
{
	sprite->sprite.setPosition(pos);
	window.draw(sprite->sprite);
}

MySprite::MySprite()
{

}


MySprite::~MySprite()
{
}
