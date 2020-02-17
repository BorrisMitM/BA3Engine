#include "LoadSceneCallback.h"
#include "GameManager.h"

void LoadSceneCallback::Setup(xml_node<>* callbackNode, string assetPath)
{
	sceneName.append(callbackNode->value());
}

void LoadSceneCallback::Invoke()
{
	GameManager::instance->LoadScene(sceneName);
}

LoadSceneCallback::LoadSceneCallback()
{
}


LoadSceneCallback::~LoadSceneCallback()
{
}
