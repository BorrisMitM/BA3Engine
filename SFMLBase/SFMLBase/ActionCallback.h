#pragma once
#include "GameAsset.h"
class ActionCallback : public GameAsset
{
	//base class for ActionCallbacks
public:
	//virtual void Setup(xml_node<>* callbackNode, string assetPath);
	virtual void Invoke();
	ActionCallback();
	~ActionCallback();
};

