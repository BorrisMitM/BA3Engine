#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "GameScene.h"
#include "SFML/Graphics.hpp"
using namespace std;
using namespace rapidxml;


class GameManager
{
private:


	map<string, GameAsset*> assets;
	GameScene* currentScene;
public:
	GameManager();
	~GameManager();

	void LoadXML(string path);

	vector<GameScene*> scenes;
	static xml_attribute<>* FindAttribute(xml_node<>* pNode, const char * name);
	static xml_node<>* FindChildNode(xml_node<>* pNode, const char * name);

	void Update(RenderWindow& window);
	struct {
		string name;
		int width;
		int height;
		int fps;
		string assetPath;
	} GameConfig;
};
