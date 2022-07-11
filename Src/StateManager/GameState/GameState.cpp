#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../Entity/Wall/Wall.hpp"
#include "../../Entity/Player/Player.hpp"

void GameState::init()
{
	loadLevel();
}

void GameState::run()
{
	//float color[3] = {0.f / 255.f, 0.f / 255.f, 0.f / 255.f};

	sf::Clock deltaClock;
	float deltaTime;

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = deltaClock.restart().asSeconds();

		Player::update(e);
		Scene::window.clear(sf::Color(0, 0, 0));
		Wall::draw();
		Player::draw();
		Scene::window.display();
	}
}

void GameState::loadLevel()
{
	const sf::Image& maze{ ResourceManager::imageMap[ImageId::maze] };
	Wall::walls.clear();
	Wall::walls.reserve(548);

	for (unsigned int y{ 0 }; y < maze.getSize().y; y++)
	{
		for (unsigned int x{ 0 }; x < maze.getSize().x; x++)
		{
			const sf::Color& color{ maze.getPixel(x, y) };

			if (color == sf::Color(0, 0, 0))
			{
				Wall::walls.emplace_back(sf::Vector2i(x, y), true);
			}
			else if (color == sf::Color(0, 255, 0))
			{
				Wall::walls.emplace_back(sf::Vector2i(x, y), false);
			}
			else if (color == sf::Color(255, 255, 0))
			{
				Player player(sf::Vector2i(x, y));
				Player::player = player;
			}
		}
	}
}
