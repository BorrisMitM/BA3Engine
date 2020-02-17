#pragma once
#include "rapidxml.hpp"
#include "SFML/Graphics.hpp"
#include <stdio.h>
#include "AnimationAsset.h"
using namespace rapidxml;
using namespace std;
using namespace sf;
class Player
{
private:
	DrawableAsset* idleAnimation;
	DrawableAsset* walkAnimation;
	bool moving;
	Vector2f targetPos;
	Vector2f moveDir;
	Vector2f spriteScale;
	int lastFrameTime;
	float  scale;
	void SetScale();
public:
	float speed, topBorder, botBorder, topScale, botScale;
	Vector2f pos;
	void Setup(xml_node<>* playerNode, map<string, GameAsset*>& assets);
	void Update(Vector2f mousePos, bool mouseDown);
	void SetIntoScene(Vector2f pos);
	void Render(RenderWindow & window);
	Player();
	~Player();
};

