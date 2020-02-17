#include "GameScene.h"
#include "GameManager.h"



void GameScene::Setup(xml_node<>* sceneNode, map<string, GameAsset*>& assets)
{
	xml_attribute<>* attr = GameManager::FindAttribute(sceneNode, "startposx");
	if (attr != NULL) startPosition.x = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "startposy");
	if (attr != NULL) startPosition.y = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "name");
	if (attr != NULL) name.append(attr->value());

	attr = GameManager::FindAttribute(sceneNode, "speed");
	if (attr != NULL) speed = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "ytop");
	if (attr != NULL) topBorder = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "ybot");
	if (attr != NULL) botBorder = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "topscale");
	if (attr != NULL) topScale = atof(attr->value());
	attr = GameManager::FindAttribute(sceneNode, "botscale");
	if (attr != NULL) botScale = atof(attr->value());

	for (xml_node<>* pChild = sceneNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "sprite") == 0) {
			MySprite* newSprite = new MySprite();
			newSprite->Setup(pChild, assets);
			attr = GameManager::FindAttribute(pChild, "layer");
			string a = attr->value();
			if (attr == NULL) {
				layerOne.push_back((MySprite*)assets[pChild->value()]);
			}
			else if (strcmp(attr->value(), "0") == 0) layerZero.push_back(newSprite);
			else if (strcmp(attr->value(), "1") == 0) layerOne.push_back(newSprite);
			else layerTwo.push_back(newSprite);
		}
		else if (strcmp(pChild->name(), "action") == 0) {
			Action* newAction = new Action();
			newAction->Setup(pChild, assets);
			actions.push_back(newAction);
		}
	}
}

void GameScene::CheckActions(RenderWindow & window, bool mouseDown, Vector2f mousePos)
{
	for (int i = 0; i < actions.size(); i++)
		actions[i]->Check(window, this, mouseDown, mousePos);
}

void GameScene::Update(RenderWindow& window)
{
	for (int i = 0; i < layerZero.size(); i++)
		layerZero[i]->Update(window);
	for (int i = 0; i < layerOne.size(); i++)
		layerOne[i]->Update(window);
	player->Render(window);
	for (int i = 0; i < layerTwo.size(); i++)
		layerTwo[i]->Update(window);
}

void GameScene::LoadScene(Player* _player)
{
	player = _player;
	player->botBorder = botBorder;
	player->topBorder = topBorder;
	player->botScale = botScale;
	player->topScale = topScale;
	player->speed = speed;
	player->SetIntoScene(startPosition);
}

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
