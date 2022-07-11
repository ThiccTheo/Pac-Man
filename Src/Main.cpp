#include <iostream>

#include "ResourceManager/ResourceManager.hpp"
#include "Scene/Scene.hpp"
#include "StateManager/StateManager.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		StateManager::addState(StateId::gameState);
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}