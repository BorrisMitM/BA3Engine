#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "GameScene.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
using namespace std;
using namespace rapidxml;

class GameManager
{
private:


	map<string, GameAsset*> assets;
	vector<string> texts;
	int currentTextIndex;
	void HandleText(bool mouseButtonDown);
public:
	static GameManager* instance;
	GameScene* currentScene;
	GameManager();
	~GameManager();
	string textToShow;
	Font font;
	Text* text;
	void LoadXML(string path);

	Player* player;
	vector<GameScene*> scenes;
	static xml_attribute<>* FindAttribute(xml_node<>* pNode, const char * name);
	static xml_node<>* FindChildNode(xml_node<>* pNode, const char * name);

	void LoadScene(string sceneName);
	void Update(RenderWindow& window, Vector2f mousePos, bool mouseButtonDown);
	void StartDialog(vector<string> texts);
	struct {
		string name;
		int width;
		int height;
		int fps;
		string assetPath;
	} GameConfig;
};

