#pragma once
#include "DrawableAsset.h"
#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"

using namespace sf;
using namespace rapidxml;
class MySprite
{
public:
	DrawableAsset* sprite;
	Vector2f pos;
	Vector2f size;
	string name;
	void Setup(xml_node<>* spriteNode, map<string, GameAsset*>& assets);
	virtual void Update(RenderWindow& window);
	bool MouseOnSprite(RenderWindow& window);
	MySprite();
	~MySprite();
};

