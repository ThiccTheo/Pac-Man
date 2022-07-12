#pragma once
#include <iostream>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class TextureId { wall, player, pellet, count };
enum class ImageId { maze, count };

class ResourceManager
{
public:
	static std::unordered_map<TextureId, sf::Texture> textureMap;
	static std::unordered_map<ImageId, sf::Image> imageMap;

	static bool load();
private:
};

