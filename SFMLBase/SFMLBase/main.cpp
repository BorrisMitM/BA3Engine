#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
bool SpriteClicked(Window *window, Sprite * sprite);
void HandleMouseButton(bool* mouseButtonDown, bool* mouseButtonUp);
int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	RectangleShape rect(Vector2f(40.f, 40.f));
	rect.setFillColor(Color::Red);
	Vector2i clickPos = Vector2i(250, 250);

	Texture texture;
	texture.loadFromFile("texture.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);
	float speed = .2f;
	Clock clock;
	float lastAction = 0;
	float duration = 1;
	int i = 0;
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
		HandleMouseButton(&mouseButtonDown, &mouseButtonUp);

		Time elapsedTime = clock.getElapsedTime();
		if (elapsedTime.asSeconds() >= lastAction + duration) {
			lastAction = elapsedTime.asSeconds();
			sprite.setColor(Color(rand() %255, rand() % 255, rand() % 255, 255));
		}
		window.clear();
		window.draw(shape);
		if (mouseButtonDown) {
			if(SpriteClicked(&window, &sprite))
				cout << "hit" << i <<endl;
			i++;
		}
		if (mouseButtonUp) {
			if (SpriteClicked(&window, &sprite))
				cout << "release" << i << endl;
			i++;
		}
		//Vector2f dir = (Vector2f)Mouse::getPosition(window) - sprite.getPosition();
		//dir = dir / sqrt(dir.x * dir.x + dir.y * dir.y);
		//sprite.setPosition(sprite.getPosition() + dir * speed);
		
		window.draw(sprite);
		window.draw(rect);
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