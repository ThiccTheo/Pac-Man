#include "Wall.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"

std::vector<Wall> Wall::walls;

Wall::Wall(const sf::Vector2i& indices)
	: Entity(indices) {}

Wall::~Wall() = default;

void Wall::draw()
{
	sf::VertexArray vertexArray;
	sf::RenderStates renderStates;
	renderStates.texture = &ResourceManager::textureMap[TextureId::wall];

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4 * walls.size());

	int quadPtr{ 0 };

	for (auto& wall : walls)
	{
		const sf::FloatRect& bodyBounds{ wall.body.getGlobalBounds() };

		wall.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
		wall.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
		wall.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
		wall.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

		sf::Vertex* currentQuad{ &vertexArray[quadPtr] };

		currentQuad[0].position = wall.mesh[0];
		currentQuad[1].position = wall.mesh[1];
		currentQuad[2].position = wall.mesh[2];
		currentQuad[3].position = wall.mesh[3];

		currentQuad[0].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentQuad[2].texCoords = sf::Vector2f(bodySize);
		currentQuad[3].texCoords = sf::Vector2f(0.f, bodySize.x);

		quadPtr += 4;
	}

	Scene::window.draw(vertexArray, renderStates);
}

