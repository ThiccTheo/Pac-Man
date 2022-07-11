#pragma once
#include <iostream>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class TextureId { count };

class ResourceManager
{
public:
	static std::unordered_map<TextureId, sf::Texture> textureMap;

	static bool load();
private:
};

