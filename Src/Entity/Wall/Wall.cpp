#include "Wall.hpp"
#include "../../Scene/Scene.hpp"

std::vector<Wall> Wall::walls;

Wall::Wall(const sf::Vector2i& indices) : Entity(indices) {}

void Wall::draw()
{
	sf::VertexArray vertexArray;
	sf::RenderStates renderStates;

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

		for (int i{ 0 }; i < 4; i++)
		{
			currentQuad[i].position = wall.mesh[i];
			currentQuad[i].color = sf::Color::Red; //temp
		}

		quadPtr += 4;
	}

	Scene::window.draw(vertexArray, renderStates);
}

