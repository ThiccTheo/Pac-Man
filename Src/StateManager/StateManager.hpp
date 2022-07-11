#pragma once
#include <iostream>
#include <stack>
#include <memory>

#include "CommonSFML.hpp"

enum class StateId { menuState, gameState, count};

class StateManager
{
public:
	virtual void init();
	virtual void run();
	const sf::Event eventHandler();
	static void addState(const StateId stateId);
	static const bool removeState();
private:
	static std::stack<std::unique_ptr<StateManager>> states;

	static void checkState();
};

