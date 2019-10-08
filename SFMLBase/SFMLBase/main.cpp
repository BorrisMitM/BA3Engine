#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include <iostream>
using namespace std;
using namespace sf;
bool SpriteClicked(Window *window, Sprite * sprite);
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp);
int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	//load texture and create sprite from it
	Texture texture;
	texture.loadFromFile("texture.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);

	Clock clock;
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

		Time elapsedTime = clock.getElapsedTime();
		
		window.draw(sprite);
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