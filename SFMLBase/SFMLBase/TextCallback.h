#pragma once
#include "ActionCallback.h"
#include "SFML/Graphics/Text.hpp"
#include "rapidxml.hpp"
#include <vector>

using namespace std;
using namespace rapidxml;
class TextCallback :
	public ActionCallback
{
private:
	vector<string> texts;
public:
	virtual void Setup(xml_node<>* callbackNode, string assetPath);
	virtual void Invoke();
	TextCallback();
	~TextCallback();
};

