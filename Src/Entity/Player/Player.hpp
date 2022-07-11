#pragma once
#include <iostream>
#include <utility>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;

	Player();
	Player(const Player&) = delete;
	Player(const sf::Vector2i& indices);
	static void update(const sf::Event& e);
	static void draw();
private:
	sf::Vector2i normalizedDirection;
	static sf::Vector2f movementOffset;
	sf::Keyboard::Key lastKeyPressed;
	std::pair<bool, bool> isBlocked;
};

