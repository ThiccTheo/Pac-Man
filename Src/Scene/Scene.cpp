#include "Scene.hpp"

bool Scene::isFocused;
sf::RenderWindow Scene::window;

void Scene::init()
{
	window.create(sf::VideoMode(896, 1152), "Pac-Man", sf::Style::Close);
	isFocused = true;
	window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);
}
