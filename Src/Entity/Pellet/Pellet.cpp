#include <algorithm>

#include "Pellet.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../Scene/Scene.hpp"

std::vector<Pellet> Pellet::pellets;

Pellet::Pellet(const sf::Vector2i& indices, const PelletSize pelletSize)
	:Entity(indices), pelletSize{ pelletSize } {}

Pellet::~Pellet() = default;

void Pellet::update()
{
	for (auto& pellet : pellets)
	{
		pellets.erase(std::remove_if(pellets.begin(), pellets.end(),
			[](Pellet& temp)
			{
				return temp.collisionHandler(EntityType::player) != nullptr;
			}), pellets.end());
	}
}

void Pellet::draw()
{
	sf::VertexArray vertexArray;
	sf::RenderStates renderStates;
	renderStates.texture = &ResourceManager::textureMap[TextureId::pellet];

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4 * pellets.size());

	int quadPtr{ 0 };

	for (auto& pellet : pellets)
	{
		const sf::FloatRect& bodyBounds{ pellet.body.getGlobalBounds() };

		pellet.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
		pellet.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
		pellet.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
		pellet.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

		sf::Vertex* currentQuad{ &vertexArray[quadPtr] };

		currentQuad[0].position = pellet.mesh[0];
		currentQuad[1].position = pellet.mesh[1];
		currentQuad[2].position = pellet.mesh[2];
		currentQuad[3].position = pellet.mesh[3];

		currentQuad[0].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentQuad[2].texCoords = sf::Vector2f(bodySize);
		currentQuad[3].texCoords = sf::Vector2f(0.f, bodySize.x);

		quadPtr += 4;
	}

	Scene::window.draw(vertexArray, renderStates);
}
