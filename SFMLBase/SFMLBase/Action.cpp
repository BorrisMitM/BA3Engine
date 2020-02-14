#include "Action.h"
#include "GameManager.h"
#include "GameScene.h"

void Action::Setup(xml_node<>* actionNode, map<string, GameAsset*>& assets)
{
	xml_attribute<>* attr = GameManager::FindAttribute(actionNode, "callbackname");
	if (attr != NULL) callbackName.append(attr->value());
	attr = GameManager::FindAttribute(actionNode, "callbackname");
	if (attr != NULL) {
		if (strcmp(attr->value(), "onClick") == 0) checkType = Check::onSprite;
		else if (strcmp(attr->value(), "onBorder") == 0) checkType = Check::onBorder;
	}
	callback = (ActionCallback*)assets[GameManager::FindAttribute(actionNode, "asset")->value()];
}

void Action::Check(RenderWindow& window, GameScene * scene, bool mouseDown, Vector2f pos)
{
	if (checkType == Check::onSprite)
	{
		if (mouseDown) {
			MySprite* sprite = NULL;
			for (int i = 0; i < scene->layerOne.size(); i++) {
				if (scene->layerOne[i]->name.compare(callbackName) == 0) {
					sprite = scene->layerOne[i];
					break;
				}
			}
			if (sprite != NULL) {
				if (sprite->MouseOnSprite(window))
					callback->Invoke();
			}
		}
	}
	
}

Action::Action()
{
}


Action::~Action()
{
}
