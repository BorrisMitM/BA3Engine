#pragma once
#include "ActionCallback.h"
#include "rapidxml.hpp"
using namespace rapidxml;
class GameScene;
enum Check { onSprite, onBorder };
class Action 
{
private:
	Check checkType;
	string callbackName;
	ActionCallback* callback;
public:
	void Setup(xml_node<>* actionNode, map<string, GameAsset*>& assets);
	void Check(RenderWindow& window, GameScene* scene, bool mouseDown, Vector2f mousePos);
	Action();
	~Action();
};

