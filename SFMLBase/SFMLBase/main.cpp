#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include "GameManager.h"
#include "MyTime.h"
#include "TextCallback.h"
using namespace std;
using namespace sf;
using namespace rapidxml;

bool SpriteClicked(Window *window, Sprite * sprite);
void HandleMouseButton(RenderWindow* window, bool* mouseButtonDown, bool* mouseButtonUp);



int main()
{
	GameManager* manager = new GameManager();
	MyTime* time = new MyTime();
	manager->LoadXML("Assets.xml");
	sf::RenderWindow window(sf::VideoMode(manager->GameConfig.width, manager->GameConfig.height), manager->GameConfig.name);
	window.setFramerateLimit(manager->GameConfig.fps);
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
		HandleMouseButton(&window, &mouseButtonDown, &mouseButtonUp);
		manager->Update(window, Vector2f(Mouse::getPosition(window)), mouseButtonDown);
		window.display();
	}

	return 0;
}

bool canMouseButtonDown = true;
bool canMouseButtonUp = true;
//sets mouseButtonDown / mouseButtonUp for one frame when the mouse is pressed / unpressed
void HandleMouseButton(RenderWindow* window, bool* mouseButtonDown, bool* mouseButtonUp) {
	//check if mouse is inside the window
	if( Mouse::isButtonPressed(Mouse::Left) ){
		if ((float)Mouse::getPosition(*window).x < 0
			|| (float)Mouse::getPosition(*window).x > window->getSize().x
			|| (float)Mouse::getPosition(*window).y < 0
			|| (float)Mouse::getPosition(*window).y > window->getSize().y)
			return;
	}
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




