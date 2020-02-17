#pragma once
#include "ActionCallback.h"
#include "SFML/Graphics/Text.hpp"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;
class TextCallback :
	public ActionCallback
{
public:
	string text;
	virtual void Setup(xml_node<>* callbackNode, string assetPath);
	virtual void Invoke();
	TextCallback();
	~TextCallback();
};

