#include "Action.h"
#include "GameManager.h"
#include "GameScene.h"

void Action::Setup(xml_node<>* actionNode, map<string, GameAsset*>& assets)
{
	xml_attribute<>* attr = GameManager::FindAttribute(actionNode, "callbackname");
	if (attr != NULL) callbackName.append(attr->value());
	attr = GameManager::FindAttribute(actionNode, "callbacktype");
	if (attr != NULL) {
		if (strcmp(attr->value(), "onClick") == 0) checkType = Check::onSprite;
		else if (strcmp(attr->value(), "onBorder") == 0) checkType = Check::onBorder;
	}
	callback = (ActionCallback*)assets[GameManager::FindAttribute(actionNode, "asset")->value()];
	attr = GameManager::FindAttribute(actionNode, "triggerdistance");
	if (attr != NULL) triggerDistance = atof(attr->value());
	else triggerDistance = 100.0;
}

void Action::Check(RenderWindow& window, GameScene * scene, bool mouseDown, Vector2f pos)
{
	if (checkType == Check::onSprite)
	{
		if (mouseDown) {
			if(clickOnSprite == NULL)
			for (int i = 0; i < scene->layerOne.size(); i++) {
				if (scene->layerOne[i]->name.compare(callbackName) == 0) {
					clickOnSprite = scene->layerOne[i];
					break;
				}
			}
			if (clickOnSprite == NULL) {
				for (int i = 0; i < scene->layerTwo.size(); i++) {
					if (scene->layerTwo[i]->name.compare(callbackName) == 0) {
						clickOnSprite = scene->layerTwo[i];
						break;
					}
				}
			}
			if (clickOnSprite != NULL) {
				if (clickOnSprite->MouseOnSprite(window))
					clickedOn = true;
				else clickedOn = false;
			}
		}
		if (clickedOn && clickOnSprite != NULL) {
			float playerX = scene->player->pos.x;
			float playerY = scene->player->pos.y;
			float distanceToPlayer = sqrtf((playerX - clickOnSprite->pos.x) * (playerX - clickOnSprite->pos.x)
				+ (playerY - clickOnSprite->pos.y) * (playerY - clickOnSprite->pos.y));
			if (distanceToPlayer <= triggerDistance)
			{
				callback->Invoke();
				scene->player->Update(scene->player->pos, true);
				clickedOn = false;
			}
		}
	}
	else if (checkType == Check::onBorder) {
		if (mouseDown) {
			if (callbackName.compare("left") == 0) {
				if (pos.x <= triggerDistance) clickedOn = true;
				else clickedOn = false;
			}
			else if (callbackName.compare("right") == 0) 
			{
				if (pos.x >= window.getSize().x - triggerDistance) clickedOn = true;
				else clickedOn = false;
			}
		}
		if (clickedOn) {
			if (callbackName.compare("left") == 0) {
				if (scene->player->pos.x <= triggerDistance) {
					clickedOn = false;
					callback->Invoke();
					scene->player->Update(scene->player->pos, true);
				}
			}
			else if (callbackName.compare("right") == 0)
			{
				if (scene->player->pos.x>= window.getSize().x - triggerDistance) {
					clickedOn = false;
					callback->Invoke();
					scene->player->Update(scene->player->pos, true);
				}
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
