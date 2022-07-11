#pragma once
#include <iostream>

#include "CommonSFML.hpp"

enum class EntityType{ player, wall, count };

class Entity
{
public:
	sf::Vector2f mesh[4];
	sf::RectangleShape body;
	static const sf::Vector2f bodySize;

	Entity();
	Entity(const sf::Vector2i& indices);
	virtual ~Entity();
	Entity* collisionHandler(const EntityType entityType);
};

