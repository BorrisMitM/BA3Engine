#pragma once
#include "DrawableAsset.h"
#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"

using namespace sf;
using namespace rapidxml;
class MySprite
{
private:
	DrawableAsset* sprite;
	Vector2f pos;
	Vector2f size;
public:
	string name;
	void Setup(xml_node<>* spriteNode, map<string, GameAsset*>& assets);
	virtual void Update(RenderWindow& window);
	MySprite();
	~MySprite();
};

