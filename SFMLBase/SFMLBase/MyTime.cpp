#include "MyTime.h"


sf::Clock* MyTime::clock = new sf::Clock();
MyTime::MyTime()
{
	clock->restart();
}


MyTime::~MyTime()
{
}
