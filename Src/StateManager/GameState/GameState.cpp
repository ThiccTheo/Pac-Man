#include "GameState.hpp"
#include "../../Scene/Scene.hpp"

void GameState::init()
{

}

void GameState::run()
{
	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		Scene::window.clear(sf::Color::White);
		Scene::window.display();
	}
}
