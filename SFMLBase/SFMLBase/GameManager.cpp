#include "GameManager.h"
#include "SpriteAsset.h"
#include "AudioAsset.h"
#include "Action.h"
#include <cstring>


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

xml_node<>* GameManager::FindChildNode(xml_node<>* pNode, const char* name) {
	for (xml_node<>* pChild = pNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), name) == 0) return pChild;
	}
	return NULL;
}

void GameManager::Update(RenderWindow& window)
{
	currentScene->Update(window);
}


xml_attribute<>* GameManager::FindAttribute(xml_node<>* pNode, const char* name) {
	for (xml_attribute<>* pAttribute = pNode->first_attribute(); pAttribute != NULL; pAttribute = pAttribute->next_attribute()) {
		if (strcmp(pAttribute->name(), name) == 0) return pAttribute;
	}
	return NULL;
}

void GameManager::LoadXML(string path) {
	ifstream MyFile(path, ios::binary);

	//get size
	streampos begin = MyFile.tellg();
	MyFile.seekg(0, ios::end);
	streampos end = MyFile.tellg();
	int nSize = end - begin;
	MyFile.seekg(0, ios::beg);
	//get file to string
	char *pText = new char[nSize + 1];
	memset(pText, 0, nSize + 1);
	MyFile.read(pText, nSize);
	MyFile.close();

	xml_document<>	doc;
	xml_attribute<>* attr;

	doc.parse<0>(pText);

	xml_node<>*	pRootNode = doc.first_node();
	xml_node<>* pNode = pRootNode;

	attr = FindAttribute(pNode, "title");
	if (attr != NULL) GameConfig.name.append(attr->value());
	attr = FindAttribute(pNode, "width");
	if (attr != NULL) GameConfig.width = atoi(attr->value());
	attr = FindAttribute(pNode, "height");
	if (attr != NULL) GameConfig.height = atoi(attr->value());
	attr = FindAttribute(pNode, "fps");
	if (attr != NULL) GameConfig.fps = atoi(attr->value());

	pNode = FindChildNode(pNode, "assetpath"); 
	if (pNode != NULL) {
		GameConfig.assetPath.append(pNode->value());
		for (xml_node<>* pChild = pNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
			if (strcmp(pChild->name(), "asset") == 0) {
				GameAsset* pAsset = NULL;
				attr = FindAttribute(pChild, "type");
				if (attr != NULL) {
					if (strcmp(attr->value(), "sprite") == 0) pAsset = new SpriteAsset();
					else if (strcmp(attr->value(), "audio") == 0) pAsset = new AudioAsset();
					if(pAsset != NULL)
						pAsset->Setup(pChild, GameConfig.assetPath);
				}
				assets.insert(pair<string, GameAsset*> (FindAttribute(pChild, "ID")->value(), pAsset));
			}
		}
	}
	for (xml_node<>* pChild = pNode->next_sibling(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "scene") == 0) {
			GameScene* pScene = new GameScene();
			pScene->Setup(pChild, assets);
			scenes.push_back(pScene);
		}
	}
	currentScene = scenes[0];
	doc.clear();
}