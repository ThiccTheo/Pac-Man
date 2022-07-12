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
	~Wall() override;
	static void draw();
};

