#include <format>

#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../Wall/Wall.hpp"

Player Player::player;
sf::Vector2f Player::movementOffset{ 4.f, 4.f };

Player::Player() = default;

Player::Player(const sf::Vector2i& indices) : Entity(indices)
{
	normalizedDirection = sf::Vector2i(1, 0);
	player.lastKeyPressed = sf::Keyboard::D;
}

Player::~Player() = default;

void Player::update(const sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		player.lastKeyPressed = e.key.code;
		break;
	}

	bool canMoveUp{ true };
	bool canMoveDown{ true };
	bool canMoveLeft{ true };
	bool canMoveRight{ true };

	for (const auto& wall : Wall::walls)
	{
		const auto& [wallX, wallY] {wall.body.getPosition()};
		const auto& [playerX, playerY] {player.body.getPosition()};

		if (wallX + bodySize.x != playerX && wallX - bodySize.x + 1.f <= playerX && wallX + bodySize.x >= playerX && wallY == playerY - bodySize.y)
		{
			canMoveUp = false;
			break;
		}
	}

	for (const auto& wall : Wall::walls)
	{
		const auto& [wallX, wallY] {wall.body.getPosition()};
		const auto& [playerX, playerY] {player.body.getPosition()};

		if (wallX + bodySize.x != playerX && wallX - bodySize.x + 1.f <= playerX && wallX + bodySize.x >= playerX && wallY == playerY + bodySize.y)
		{
			canMoveDown = false;
			break;
		}
	}

	for (const auto& wall : Wall::walls)
	{
		const auto& [wallX, wallY] {wall.body.getPosition()};
		const auto& [playerX, playerY] {player.body.getPosition()};

		if (wallY + bodySize.y != playerY && wallY - bodySize.y + 1.f <= playerY && wallY + bodySize.y >= playerY && wallX == playerX - bodySize.x)
		{
			canMoveLeft = false;
			break;
		}
	}


	for (const auto& wall : Wall::walls)
	{
		const auto& [wallX, wallY] {wall.body.getPosition()};
		const auto& [playerX, playerY] {player.body.getPosition()};

		if (wallY + bodySize.y != playerY && wallY - bodySize.y + 1.f <= playerY && wallY + bodySize.y >= playerY && wallX == playerX + bodySize.x)
		{
			canMoveRight = false;
			break;
		}
	}

	switch (player.lastKeyPressed)
	{
	case sf::Keyboard::W:
		if (canMoveUp)
		{
		
			player.normalizedDirection = sf::Vector2i(0, -1);
		}
		break;
	case sf::Keyboard::S:
		if (canMoveDown)
		{
			player.normalizedDirection = sf::Vector2i(0, 1);
		}
		break;
	case sf::Keyboard::A:
		if (canMoveLeft)
		{
			player.normalizedDirection = sf::Vector2i(-1, 0);
		}
		break;
	case sf::Keyboard::D:
		if (canMoveRight)
		{
			player.normalizedDirection = sf::Vector2i(1, 0);
		}
		break;
	}

	Entity* collider{ nullptr };

	player.body.move(movementOffset.x * player.normalizedDirection.x, 0.f);

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
	renderStates.texture = &ResourceManager::textureMap[TextureId::player];

	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	int quadPtr{ 0 };

	const sf::FloatRect& bodyBounds{ player.body.getGlobalBounds() };

	player.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
	player.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
	player.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
	player.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

	sf::Vertex* currentQuad{ &vertexArray[quadPtr] };

	currentQuad[0].position = player.mesh[0];
	currentQuad[1].position = player.mesh[1];
	currentQuad[2].position = player.mesh[2];
	currentQuad[3].position = player.mesh[3];

	switch (player.normalizedDirection.x)
	{
	case 1:
		currentQuad[0].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentQuad[2].texCoords = sf::Vector2f(bodySize);
		currentQuad[3].texCoords = sf::Vector2f(0.f, bodySize.x);
		break;
	case -1:
		currentQuad[0].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[2].texCoords = sf::Vector2f(0.f, bodySize.x);
		currentQuad[3].texCoords = sf::Vector2f(bodySize);
		break;
	}

	switch (player.normalizedDirection.y)
	{
	case 1:
		currentQuad[0].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(0.f, bodySize.x);
		currentQuad[2].texCoords = sf::Vector2f(bodySize);
		currentQuad[3].texCoords = sf::Vector2f(bodySize.x, 0.f);
		break;
	case -1:
		currentQuad[3].texCoords = sf::Vector2f(0.f, bodySize.x);
		currentQuad[2].texCoords = sf::Vector2f(0.f, 0.f);
		currentQuad[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentQuad[0].texCoords = sf::Vector2f(bodySize);
		break;
	}

	quadPtr += 4;

	Scene::window.draw(vertexArray, renderStates);
}
