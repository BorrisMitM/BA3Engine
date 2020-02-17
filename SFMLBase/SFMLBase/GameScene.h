#pragma once
#include "SpriteAsset.h"
#include "MySprite.h"
#include "Action.h"
#include <stdio.h>
#include <vector>
#include "rapidxml.hpp"
#include "Player.h"

class GameScene
{
public:
	Player* player;
	string name;
	vector<MySprite*> layerZero; // background
	vector<MySprite*> layerOne;	// behind player
	vector<MySprite*> layerTwo;  // in front of player
	vector<Action*> actions;
	Vector2f startPosition;
	float topBorder, botBorder, topScale, botScale, speed;
	void Setup(xml_node<>* sceneNode, map<string, GameAsset*>& assets);
	void CheckActions(RenderWindow& window, bool mouseDown, Vector2f mousePos);
	void Update(RenderWindow& window);
	void LoadScene(Player* _player);
	GameScene();
	~GameScene();
};