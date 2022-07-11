#include <iostream>

#include "ResourceManager/ResourceManager.hpp"
#include "Scene/Scene.hpp"
#include "StateManager/StateManager.hpp"
#include "CommonImGui.hpp"
#include "CommonSFML.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		StateManager::addState(StateId::menuState);
		ImGui::SFML::Shutdown(Scene::window);
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}