#pragma once
#include "SFML/Graphics.hpp"
#include "GameAsset.h"
class DrawableAsset : public GameAsset
{
public:
	Texture texture;
	virtual void Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale);
	DrawableAsset();
	~DrawableAsset();
};

