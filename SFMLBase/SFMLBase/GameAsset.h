#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include "rapidxml.hpp"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;

class GameAsset
{
public:
	string ID;
	virtual void Setup(xml_node<>* pNode, string assetPath);

	GameAsset();
	~GameAsset();
};

