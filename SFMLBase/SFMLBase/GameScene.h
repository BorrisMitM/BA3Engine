#pragma once
#include "GameAsset.h"
#include <vector>
class GameScene
{
public:
	string name;
	vector<GameAsset*> assets;
	GameScene();
	~GameScene();
};

