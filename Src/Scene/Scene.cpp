#include "Scene.hpp"

bool Scene::isFocused;
sf::RenderWindow Scene::window;

void Scene::init()
{
	window.create(sf::VideoMode(600, 800), "Pac-Man", sf::Style::Default);
	isFocused = true;
	window.setVerticalSyncEnabled(true);
}
