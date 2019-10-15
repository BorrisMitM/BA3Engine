#pragma once
#include "rapidxml.hpp"
#include "GameScene.h"
using namespace rapidxml;
class XMLParser
{
	xml_node<>* FindChildNode(xml_node<>* pNode, const char* name);
	xml_attribute<>* FindAttribute(xml_node<>* pNode, const char* name);
public:
	static void LoadXML(vector<GameScene*>* scenes);
	XMLParser();
	~XMLParser();
};

