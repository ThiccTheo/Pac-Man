#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"

class Scene
{
public:
	static sf::RenderWindow window;
	static bool isFocused;

	static void init();
};

