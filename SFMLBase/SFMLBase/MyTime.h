#pragma once
#include "SFML/Graphics.hpp"
class MyTime
{
//small helper class to have a static clock
public:
	static sf::Clock* clock;
	MyTime();
	~MyTime();
};

