#include "MySprite.h"
#include "GameManager.h"


void MySprite::Setup(xml_node<>* spriteNode, map<string, GameAsset*>& assets)
{
	sprite = (DrawableAsset*)assets[spriteNode->value()];
	xml_attribute<>* attr = GameManager::FindAttribute(spriteNode, "posx");
	if(attr != NULL)pos.x = atoi(attr->value());
	attr = GameManager::FindAttribute(spriteNode, "posy");
	if (attr != NULL)pos.y = atoi(attr->value());
	
	attr = GameManager::FindAttribute(spriteNode, "sizex");
	if (attr != NULL)size.x = atof(attr->value());
	else size.x = 1;
	attr = GameManager::FindAttribute(spriteNode, "sizey");
	if (attr != NULL)size.y = atof(attr->value());
	else size.y = 1;
}

void MySprite::Update(RenderWindow & window)
{
	sprite->Update(window, pos, size);
}

MySprite::MySprite()
{

}


MySprite::~MySprite()
{
}
