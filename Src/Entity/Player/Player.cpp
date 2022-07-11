#include "Player.hpp"
#include "../../Scene/Scene.hpp"

Player Player::player;
sf::Vector2f Player::movementOffset{10.f, 10.f};

Player::Player() = default;

Player::Player(const sf::Vector2i& indices) : Entity(indices)
{
	normalizedDirection = sf::Vector2i(1, 0);
}

void Player::update()
{


	player.body.move(movementOffset.x * player.normalizedDirection.x, 0.f);

	const Entity* collider{ nullptr };

	collider = player.collisionHandler(EntityType::wall);
	if (collider != nullptr)
	{
		if (player.normalizedDirection.x > 0)
		{
			player.body.setPosition(collider->body.getPosition().x - bodySize.x, player.body.getPosition().y);
		}
		else if (player.normalizedDirection.x < 0)
		{
			player.body.setPosition(collider->body.getPosition().x + bodySize.x, player.body.getPosition().y);
		}
	}

	player.body.move(0.f, movementOffset.y * player.normalizedDirection.y);

	collider = player.collisionHandler(EntityType::wall);
	if (collider != nullptr)
	{
		if (player.normalizedDirection.y > 0)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y - bodySize.y);
		}
		else if (player.normalizedDirection.y < 0)
		{
			player.body.setPosition(player.body.getPosition().x, collider->body.getPosition().y + bodySize.y);
		}
	}
}

void Player::draw()
{
	sf::VertexArray vertexArray;
	sf::RenderStates renderStates;

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	int quadPtr{ 0 };

	const sf::FloatRect& bodyBounds{ player.body.getGlobalBounds() };

	player.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
	player.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
	player.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
	player.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

	sf::Vertex* currentQuad{ &vertexArray[quadPtr] };

	for (int i{ 0 }; i < 4; i++)
	{
		currentQuad[i].position = player.mesh[i];
		currentQuad[i].color = sf::Color(255, 255, 0);
	}

	quadPtr += 4;

	Scene::window.draw(vertexArray, renderStates);
}
