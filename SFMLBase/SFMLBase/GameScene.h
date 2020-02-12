#pragma once
#include "SpriteAsset.h"
#include "MySprite.h"
#include "Action.h"
#include <stdio.h>
#include <vector>
#include "rapidxml.hpp"
class GameScene
{
public:
	string name;
	vector<MySprite*> layerZero; // background
	vector<MySprite*> layerOne;	// behind player
	vector<MySprite*> layerTwo;  // in front of player
	vector<Action*> actions;
	Vector2i startPosition;
	void Setup(xml_node<>* sceneNode, map<string, GameAsset*>& assets);
	void Update(RenderWindow& window);
	GameScene();
	~GameScene();
};