#pragma once
#include <iostream>

#include "../StateManager.hpp"

class GameState : public StateManager
{
public:
	void init() override;
	void run() override;
};

