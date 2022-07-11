#include "Entity.hpp"

const sf::Vector2f Entity::bodySize{ 32.f, 32.f };

Entity::Entity(const sf::Vector2i& indices)
{
	body.setSize(bodySize);
	body.setPosition(indices.x * bodySize.x, indices.y * bodySize.y);
}
