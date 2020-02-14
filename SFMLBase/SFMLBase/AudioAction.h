#pragma once
#include "ActionCallback.h"
#include "SFML/Audio.hpp"
using namespace sf;
class AudioAction :
	public ActionCallback
{
private:
	SoundBuffer buffer;
	Sound sound;
public:
	virtual void Setup(xml_node<>* callbackNode, string assetPath);
	virtual void Invoke();
	AudioAction();
	~AudioAction();
};

