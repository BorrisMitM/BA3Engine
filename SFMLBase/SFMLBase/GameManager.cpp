#include "GameManager.h"
#include "SpriteAsset.h"
#include "AnimationAsset.h"
#include "Action.h"
#include "AudioAction.h"
#include "LoadSceneCallback.h"
#include "TextCallback.h"
#include "MyTime.h"
#include <cstring>
#include <iostream>


GameManager* GameManager::instance = NULL;


GameManager::GameManager()
{
	if (instance == NULL) instance = this;//Singelton
	else delete(this);
}


GameManager::~GameManager()
{
}



void GameManager::LoadScene(string sceneName)
{
	for (int i = 0; i < scenes.size(); i++) {
		if (sceneName.compare(scenes[i]->name) == 0) {
			currentScene = scenes[i];
			currentScene->LoadScene(player);
		}
	}
}

void GameManager::Update(RenderWindow& window, Vector2f mousePos, bool mouseButtonDown)
{
	currentScene->Update(window);//Renders everything in the scene to the window
	HandleText(mouseButtonDown);
	if (texts.size() > 0) {
		if (texts[currentTextIndex].compare(text->getString()) != 0) {
			text->setString(texts[currentTextIndex]);
			text->setOrigin(text->getGlobalBounds().width / 2.0, text->getGlobalBounds().height);
		}
		window.draw(*text);
	}
	else {
		//don't let player move or interact with other objects while text gets displayed
		player->Update(mousePos, mouseButtonDown);
		currentScene->CheckActions(window, mouseButtonDown, mousePos);
	}
}



void GameManager::LoadXML(string path) {

	//XML Setup
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

	//General GameConfig data
	attr = FindAttribute(pNode, "title");
	if (attr != NULL) GameConfig.name.append(attr->value());
	attr = FindAttribute(pNode, "assetpath");
	if (attr != NULL) GameConfig.assetPath.append(attr->value());
	attr = FindAttribute(pNode, "width");
	if (attr != NULL) GameConfig.width = atoi(attr->value());
	attr = FindAttribute(pNode, "height");
	if (attr != NULL) GameConfig.height = atoi(attr->value());
	attr = FindAttribute(pNode, "fps");
	if (attr != NULL) GameConfig.fps = atoi(attr->value());


	//textpreferences
	pNode = FindChildNode(pRootNode, "textpreferences");
	if (pNode) {
		attr = FindAttribute(pNode, "font");
		font.loadFromFile(GameConfig.assetPath + attr->value());
		text = new Text("", font);
		attr = FindAttribute(pNode, "size");
		if (attr != NULL) text->setCharacterSize(atoi(attr->value()));
		else text->setCharacterSize(50);
		text->setFillColor(Color(255, 255, 255, 255));
		int xPos = 500;
		int yPos = 100;
		attr = FindAttribute(pNode, "posx");
		if (attr != NULL) xPos = atoi(attr->value());
		attr = FindAttribute(pNode, "posy");
		if (attr != NULL) yPos = atoi(attr->value());
		text->setPosition(Vector2f(xPos, yPos));
		text->setOrigin(text->getGlobalBounds().width / 2.0, text->getGlobalBounds().height);
	}

	//assets
	pNode = FindChildNode(pRootNode, "assets");
	if (pNode != NULL) {
		for (xml_node<>* pChild = pNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
			if (strcmp(pChild->name(), "asset") == 0) {
				GameAsset* pAsset = NULL;
				attr = FindAttribute(pChild, "type");
				if (attr != NULL) {
					if (strcmp(attr->value(), "sprite") == 0) pAsset = new SpriteAsset();
					else if (strcmp(attr->value(), "audio") == 0) pAsset = new AudioAction();
					else if (strcmp(attr->value(), "anim") == 0) pAsset = new AnimationAsset();
					else if (strcmp(attr->value(), "loadScene") == 0) pAsset = new LoadSceneCallback();
					else if (strcmp(attr->value(), "dialog") == 0) pAsset = new TextCallback();

					if(pAsset != NULL)
						pAsset->Setup(pChild, GameConfig.assetPath);
				}
				assets.insert(pair<string, GameAsset*> (FindAttribute(pChild, "ID")->value(), pAsset));
			}
		}
	}
	//player and scenes need assets to be loaded already

	//player
	player = new Player();
	player->Setup(FindChildNode(pRootNode, "player"), assets);

	//scenes 
	for (xml_node<>* pChild = pNode->next_sibling(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "scene") == 0) {
			GameScene* pScene = new GameScene();
			pScene->Setup(pChild, assets);
			scenes.push_back(pScene);
		}
	}
	currentScene = scenes[0];
	currentScene->LoadScene(player);
	doc.clear();
}

//Dialog Handling
void GameManager::StartDialog(vector<string> _texts)
{
	currentTextIndex = 0;
	texts = _texts;
}

void GameManager::HandleText(bool mouseButtonDown)
{
	if (texts.size() > 0) {
		if (mouseButtonDown) {
			currentTextIndex++;
			if (currentTextIndex >= texts.size()) {
				texts.clear();
				return;
			}
		}
	}
}

//XML helper functions
xml_node<>* GameManager::FindChildNode(xml_node<>* pNode, const char* name) {
	for (xml_node<>* pChild = pNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), name) == 0) return pChild;
	}
	return NULL;
}

xml_attribute<>* GameManager::FindAttribute(xml_node<>* pNode, const char* name) {
	for (xml_attribute<>* pAttribute = pNode->first_attribute(); pAttribute != NULL; pAttribute = pAttribute->next_attribute()) {
		if (strcmp(pAttribute->name(), name) == 0) return pAttribute;
	}
	return NULL;
}