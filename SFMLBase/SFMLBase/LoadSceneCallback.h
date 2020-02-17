#pragma once
#include "ActionCallback.h"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;
class LoadSceneCallback :
	public ActionCallback
{
private:
	string sceneName;
public:
	virtual void Setup(xml_node<>* callbackNode, string assetPath);
	virtual void Invoke();
	LoadSceneCallback();
	~LoadSceneCallback();
};

