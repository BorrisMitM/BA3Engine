#pragma once
#include "ActionCallback.h"
#include "rapidxml.hpp"
#include "MySprite.h"
using namespace rapidxml;
class GameScene;
enum Check { onSprite, onBorder };
class Action 
{
private:
	Check checkType;
	string callbackName;
	ActionCallback* callback;
	bool clickedOn;
	float triggerDistance;
	MySprite* clickOnSprite;
public:
	void Setup(xml_node<>* actionNode, map<string, GameAsset*>& assets);
	void Check(RenderWindow& window, GameScene* scene, bool mouseDown, Vector2f mousePos);
	Action();
	~Action();
};

