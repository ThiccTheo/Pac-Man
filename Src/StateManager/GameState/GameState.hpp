#pragma once
#include <iostream>

#include "../StateManager.hpp"
#include "CommonImGui.hpp"
#include "CommonSFML.hpp"

class GameState : public StateManager
{
public:
	void init() override;
	void run() override;
private:
	void loadLevel();
};

