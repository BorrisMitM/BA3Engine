#pragma once
#include "DrawableAsset.h"
#include "SFML/Graphics.hpp"
class AnimationAsset : public DrawableAsset
{
	Texture texture;
	Sprite sprite;
	int width, height, amount,  offset, currentFrame, nextFrameChange, columns;
	float duration;
public:
	virtual void Setup(xml_node<>* spriteNode, string assetPath);
	virtual void Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale);
	AnimationAsset();
	~AnimationAsset();
};

