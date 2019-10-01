#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
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
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Time elapsedTime = clock.getElapsedTime();
		if (elapsedTime.asSeconds() >= lastAction + duration) {
			lastAction = elapsedTime.asSeconds();
			sprite.setColor(Color(255, 255, 255, rand() % 256));
			cout << "changed color" << endl;
		}
		window.clear();
		window.draw(shape);
		//if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2f dir = (Vector2f)Mouse::getPosition(window) - sprite.getPosition();
		dir = dir / sqrt(dir.x * dir.x + dir.y * dir.y);
		sprite.setPosition(sprite.getPosition() + dir * speed);
		
		window.draw(sprite);
		window.draw(rect);
		window.display();
	}

	return 0;
}