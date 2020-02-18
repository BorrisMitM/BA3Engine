#pragma once
#include "SFML/Graphics.hpp"
#include "GameAsset.h"
class DrawableAsset : public GameAsset
{
	//base class for drawable GameAssets
public:
	Texture texture;
	virtual void Update(sf::RenderWindow & window, Vector2f pos, Vector2f scale);
	DrawableAsset();
	~DrawableAsset();
};

