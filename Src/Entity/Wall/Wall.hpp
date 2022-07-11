#pragma once
#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Wall : public Entity
{
public:
	static std::vector<Wall> walls;
	const bool isSolid;

	Wall(const sf::Vector2i& indices, const bool isSolid);
	~Wall() override;
	static void draw();
};

