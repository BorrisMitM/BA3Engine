#include "MySprite.h"
#include "GameManager.h"


void MySprite::Setup(xml_node<>* spriteNode, map<string, GameAsset*>& assets)
{
	name = spriteNode->value();
	xml_attribute<>* attr = GameManager::FindAttribute(spriteNode, "posx");
	if(attr != NULL)pos.x = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "posy");
	if (attr != NULL)pos.y = atoi(attr->value());

	attr = GameManager::FindAttribute(spriteNode, "asset");
	if(attr!= NULL) sprite = (DrawableAsset*)assets[attr->value()];
	attr = GameManager::FindAttribute(spriteNode, "sizex");
	if (attr != NULL)size.x = atof(attr->value());
	else size.x = 1;
	attr = GameManager::FindAttribute(spriteNode, "sizey");
	if (attr != NULL)size.y = atof(attr->value());
	else size.y = 1;
}

void MySprite::Update(RenderWindow & window)
{
	sprite->Update(window, pos, size); //can be animation or static sprite
}

bool MySprite::MouseOnSprite(RenderWindow & window)
{
	if ((float)Mouse::getPosition(window).x >= pos.x - sprite->texture.getSize().x * size.x / 2.0
		&& (float)Mouse::getPosition(window).x <= pos.x + sprite->texture.getSize().x * size.x / 2.0
		&& (float)Mouse::getPosition(window).y >= pos.y - sprite->texture.getSize().y * size.y / 2.0
		&& (float)Mouse::getPosition(window).y <= pos.y + sprite->texture.getSize().y * size.y / 2.0)
		return true;
	return false;
}

MySprite::MySprite()
{

}


MySprite::~MySprite()
{
}
