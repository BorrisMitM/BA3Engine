#include "AudioAction.h"
#include "GameManager.h"


void AudioAction::Setup(xml_node<>* callbackNode, string assetPath)
{
	buffer.loadFromFile(assetPath + callbackNode->value());
	xml_attribute<>* attr = GameManager::FindAttribute(callbackNode, "ID");
	if (attr != NULL) ID.append(attr->value());
}

void AudioAction::Invoke()
{
	sound.setBuffer(buffer);
	sound.play();
}

AudioAction::AudioAction()
{
}


AudioAction::~AudioAction()
{
}
