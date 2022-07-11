#pragma once
#include <iostream>

#include "CommonSFML.hpp"

class Entity
{
public:
	sf::Vector2f mesh[4];
	sf::RectangleShape body;
	static const sf::Vector2f bodySize;

	Entity(const sf::Vector2i& indices);
};

