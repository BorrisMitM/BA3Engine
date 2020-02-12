#include "GameScene.h"
#include "GameManager.h"



void GameScene::Setup(xml_node<>* sceneNode, map<string, GameAsset*>& assets)
{
	xml_attribute<>* attr;
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

		}
	}
}

void GameScene::Update(RenderWindow& window)
{
	for (int i = 0; i < layerZero.size(); i++)
		layerZero[i]->Update(window);
	for (int i = 0; i < layerOne.size(); i++)
		layerOne[i]->Update(window);
	for (int i = 0; i < layerTwo.size(); i++)
		layerTwo[i]->Update(window);
}

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}