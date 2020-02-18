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
	map<string, GameAsset*> assets;	//map of all Assets accesable through the right ID
	GameScene* currentScene;
	Player* player;
	vector<GameScene*> scenes;
	
	//text display independent of the current scene
	vector<string> texts;
	int currentTextIndex;					
	void HandleText(bool mouseButtonDown);
	string textToShow;
	Font font;
	Text* text;
public:
	static GameManager* instance; // Singelton so it does not have to get passed through multiple Update functions to get a reference
	GameManager();
	~GameManager();

	void LoadXML(string path);
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

