#pragma once
#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

enum class PelletSize { small, large, count };

class Pellet : public Entity
{
public:
	PelletSize pelletSize;
	static std::vector<Pellet> pellets;

	Pellet(const sf::Vector2i& indices, const PelletSize pelletSize);
	~Pellet() override;
	static void update();
	static void draw();
};

