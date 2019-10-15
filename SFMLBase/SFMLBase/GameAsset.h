#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
class GameAsset
{
public:
	string ID;
	int type;
	string fileName;
	GameAsset();
	~GameAsset();
};

