#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include "GameScene.h"
using namespace std;
using namespace sf;
using namespace rapidxml;
bool SpriteClicked(Window *window, Sprite * sprite);
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp);
void LoadXML(vector<GameScene*>* scenes);
struct {
	string name;
	int width;
	int height;
	int fps;
	string assetPath;
} GameConfig;

int main()
{
	vector<GameScene*> scenes;
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	//load texture and create sprite from it
	Texture texture;
	texture.loadFromFile("texture.jpg");
	Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);
	list<Sprite*> sprites;
	LoadXML(&scenes);
	Clock clock;
	bool mouseButtonDown = false;
	bool mouseButtonUp = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		HandleMouseButton(&mouseButtonDown, &mouseButtonUp);

		Time elapsedTime = clock.getElapsedTime();

		window.draw(sprite);
		window.display();
	}

	return 0;
}

bool SpriteClicked(Window* window, Sprite* sprite) {
	if ((float)Mouse::getPosition(*window).x >= sprite->getPosition().x
		&& (float)Mouse::getPosition(*window).x <= sprite->getPosition().x + sprite->getTextureRect().width
		&& (float)Mouse::getPosition(*window).y >= sprite->getPosition().y
		&& (float)Mouse::getPosition(*window).y <= sprite->getPosition().y + sprite->getTextureRect().height)
		return true;
	return false;
}
bool canMouseButtonDown = true;
bool canMouseButtonUp = true;
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp) {
	if (!(*mouseButtonDown) && Mouse::isButtonPressed(Mouse::Left) && canMouseButtonDown) {
		*mouseButtonDown = true;
		canMouseButtonDown = false;
		canMouseButtonUp = true;
	}
	else if (*mouseButtonDown)
		*mouseButtonDown = false;
	else if (!(*mouseButtonUp) && !Mouse::isButtonPressed(Mouse::Left) && canMouseButtonUp) {
		*mouseButtonUp = true;
		canMouseButtonDown = true;
		canMouseButtonUp = false;
	}
	else if (*mouseButtonUp)
		*mouseButtonUp = false;

}

xml_node<>* FindChildNode(xml_node<>* pNode, const char* name) {
	for (xml_node<>* pChild = pNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), name) == 0) return pChild;
	}
	return NULL;
}


xml_attribute<>* FindAttribute(xml_node<>* pNode, const char* name) {
	for (xml_attribute<>* pAttribute = pNode->first_attribute(); pAttribute != NULL; pAttribute = pAttribute->next_attribute()) {
		if (strcmp(pAttribute->name(), name) == 0) return pAttribute;
	}
	return NULL;
}

void LoadXML(vector<GameScene*>* scenes) {
	ifstream MyFile("Assets.xml", ios::binary);

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
	if (pNode != NULL) GameConfig.assetPath.append(pNode->value());
	for (xml_node<>* pChild = pRootNode->first_node(); pChild != NULL; pChild = pChild->next_sibling()) {
		if (strcmp(pChild->name(), "scene") == 0) {
			GameScene* pScene = new GameScene();

			attr = FindAttribute(pChild, "name");
			if (attr != NULL) pScene->name.append(attr->value());
			pNode = FindChildNode(pChild, "assets");
			if (pNode != NULL) {
				for (xml_node<>* pAssets = pNode->first_node(); pAssets != NULL; pAssets = pAssets->next_sibling()) {
					if (strcmp(pAssets->name(), "asset") == 0) {
						GameAsset* pAsset = new GameAsset();
						pAsset->fileName.append(pAssets->value());
						attr = FindAttribute(pAssets, "id");
						if (attr != NULL) pAsset->ID.append(attr->value());
						attr = FindAttribute(pAssets, "type");
						if (strcmp(attr->value(), "sprite") == 0) pAsset->type = 0;
						if (strcmp(attr->value(), "audio") == 0) pAsset->type = 1;

						pScene->assets.push_back(pAsset);
					}
				}
			}
			scenes->push_back(pScene);
		}
	}
	doc.clear();
}


