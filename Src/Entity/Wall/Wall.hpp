#pragma once
#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Wall : public Entity
{
public:
	static std::vector<Wall> walls;

	Wall(const sf::Vector2i& indices);
	static void draw();
};

