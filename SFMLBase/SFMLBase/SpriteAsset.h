#pragma once
#include "DrawableAsset.h"
class SpriteAsset :
	public DrawableAsset
{
protected:
	Texture texture;

public:
	Sprite sprite;
	virtual void Setup(xml_node<>* spriteNode, string assetPath);
	virtual void Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale);
	SpriteAsset();
	~SpriteAsset();
};

