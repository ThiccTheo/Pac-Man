#include "Entity.hpp"
#include "Player/Player.hpp"
#include "Wall/Wall.hpp"

const sf::Vector2f Entity::bodySize{ 32.f, 32.f };

Entity::Entity() = default;

Entity::Entity(const sf::Vector2i& indices)
{
	body.setSize(bodySize);
	body.setPosition(indices.x * bodySize.x, indices.y * bodySize.y);
}

const Entity* Entity::collisionHandler(const EntityType entityType)
{
	switch (entityType)
	{
		case EntityType::wall:
			for (const auto& wall : Wall::walls)
			{
				if (body.getGlobalBounds().intersects(wall.body.getGlobalBounds()))
				{
					return &wall;
				}
			}
			break;
		case EntityType::player:
			if (body.getGlobalBounds().intersects(Player::player.body.getGlobalBounds()))
			{
				return &Player::player;
			}
			break;
	}

	return nullptr;
}
