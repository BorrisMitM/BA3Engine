#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include "GameManager.h"
#include "MyTime.h"
using namespace std;
using namespace sf;
using namespace rapidxml;

bool SpriteClicked(Window *window, Sprite * sprite);
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp);



int main()
{
	GameManager* manager = new GameManager();
	MyTime* time = new MyTime();
	manager->LoadXML("Assets.xml");
	sf::RenderWindow window(sf::VideoMode(manager->GameConfig.width, manager->GameConfig.height), manager->GameConfig.name);
	bool mouseButtonDown = false;
	bool mouseButtonUp = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		HandleMouseButton(&mouseButtonDown, &mouseButtonUp);
		manager->Update(window);
		window.display();
	}

	return 0;
}

bool SpriteClicked(Window* window, Sprite* sprite) {
	if ((float)Mouse::getPosition(*window).x >= sprite->getPosition().x
		&& (float)Mouse::getPosition(*window).x <= sprite->getPosition().x + sprite->getTextureRect().width
		&& (float)Mouse::getPosition(*window).y >= sprite->getPosition().y
		&& (float)Mouse::getPosition(*window).y <= sprite->getPosition().y + sprite->getTextureRect().height)
		return true;
	return false;
}
bool canMouseButtonDown = true;
bool canMouseButtonUp = true;
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp) {
	if (!(*mouseButtonDown) && Mouse::isButtonPressed(Mouse::Left) && canMouseButtonDown) {
		*mouseButtonDown = true;
		canMouseButtonDown = false;
		canMouseButtonUp = true;
	}
	else if (*mouseButtonDown)
		*mouseButtonDown = false;
	else if (!(*mouseButtonUp) && !Mouse::isButtonPressed(Mouse::Left) && canMouseButtonUp) {
		*mouseButtonUp = true;
		canMouseButtonDown = true;
		canMouseButtonUp = false;
	}
	else if (*mouseButtonUp)
		*mouseButtonUp = false;

}




