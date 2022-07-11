#include "MenuState.hpp"
#include "../../Scene/Scene.hpp"

void MenuState::init()
{
}

void MenuState::run()
{
	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		switch (e.type)
		{
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Space)
				{
					addState(StateId::gameState);
				}
				break;
		}

		Scene::window.clear();
		Scene::window.display();
	}
}
