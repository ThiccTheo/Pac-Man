#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../Entity/Wall/Wall.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Pellet/Pellet.hpp"

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

		//ImGui::SFML::ProcessEvent(e);

		deltaTime = deltaClock.restart().asSeconds();

		//ImGui::SFML::Update(Scene::window, sf::seconds(deltaTime));

		//ImGui::ColorEdit3("Clear Color", color);

		Player::update(e);
		Pellet::update();
		//Scene::window.clear(sf::Color(color[0] * 255, color[1] * 255, color[2] * 255));
		Scene::window.clear(sf::Color(0, 95, 140));
		Wall::draw();
		Pellet::draw();
		Player::draw();
		//ImGui::SFML::Render(Scene::window);
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
				Wall::walls.emplace_back(sf::Vector2i(x, y));
			}
			else if (color == sf::Color(255, 255, 0))
			{
				Player player(sf::Vector2i(x, y));
				Player::player = player;
			}
			else if (color == sf::Color(255, 255, 255))
			{
				Pellet::pellets.emplace_back(sf::Vector2i(x, y), PelletSize::small);
			}
			else if (color == sf::Color(255, 0, 0))
			{
				Pellet::pellets.emplace_back(sf::Vector2i(x, y), PelletSize::large);
			}
		}
	}
}
