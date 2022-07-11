#include "ResourceManager.hpp"

std::unordered_map<TextureId, sf::Texture> ResourceManager::textureMap;
std::unordered_map<ImageId, sf::Image> ResourceManager::imageMap;

bool ResourceManager::load()
{
	return
		imageMap[ImageId::maze].loadFromFile("Data/Images/Maze.png");
}
