#pragma once
#include "GameAsset.h"
class SpriteAsset :
	public GameAsset
{
private:
	Texture texture;

public:
	Sprite sprite;
	virtual void Setup(xml_node<>* spriteNode, string assetPath);
	SpriteAsset();
	~SpriteAsset();
};

