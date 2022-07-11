#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;

	Player();
	Player(const Player&) = delete;
	Player(const sf::Vector2i& indices);
	static void update();
	static void draw();
private:
	sf::Vector2i normalizedDirection;
	static sf::Vector2f movementOffset;
};

