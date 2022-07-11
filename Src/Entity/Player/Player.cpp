#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../Wall/Wall.hpp"

Player Player::player;
sf::Vector2f Player::movementOffset{4.f, 4.f};

Player::Player() = default;

Player::Player(const sf::Vector2i& indices) : Entity(indices)
{
	normalizedDirection = sf::Vector2i(1, 0);
	onCorner.first = false;
	onCorner.second = false;
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

	if (player.lastKeyPressed == sf::Keyboard::W && player.onCorner.first)
	{
		player.normalizedDirection.y = -1;
		player.normalizedDirection.x = 0;
		player.onCorner.first = false;
	}
	else if (player.lastKeyPressed == sf::Keyboard::S && player.onCorner.first)
	{
		player.normalizedDirection.y = 1;
		player.normalizedDirection.x = 0;
		player.onCorner.first = false;
	}
	else if (player.lastKeyPressed == sf::Keyboard::A && player.onCorner.second)
	{
		player.normalizedDirection.x = -1;
		player.normalizedDirection.y = 0;
		player.onCorner.second = false;
	}
	else if (player.lastKeyPressed == sf::Keyboard::D && player.onCorner.second)
	{
		player.normalizedDirection.x = 1;
		player.normalizedDirection.y = 0;
		player.onCorner.second = false;
	}


	player.body.move(movementOffset.x * player.normalizedDirection.x, 0.f);

	Entity* collider{ nullptr };

	collider = player.collisionHandler(EntityType::wall);
	if (collider != nullptr && dynamic_cast<Wall*>(collider)->isSolid)
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
	else if (collider != nullptr && !dynamic_cast<Wall*>(collider)->isSolid)
	{
		player.onCorner.first = true;
		if (player.lastKeyPressed == sf::Keyboard::A || player.lastKeyPressed == sf::Keyboard::D)
		{
			player.body.setPosition(collider->body.getPosition());
		}
	}

	player.body.move(0.f, movementOffset.y * player.normalizedDirection.y);

	collider = player.collisionHandler(EntityType::wall);
	if (collider != nullptr && dynamic_cast<Wall*>(collider)->isSolid)
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
	else if (collider != nullptr && !dynamic_cast<Wall*>(collider)->isSolid)
	{
		player.onCorner.second = true;
		if (player.lastKeyPressed == sf::Keyboard::W || player.lastKeyPressed == sf::Keyboard::S)
		{
			player.body.setPosition(collider->body.getPosition());
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
			currentQuad[0].texCoords = sf::Vector2f(0.f, bodySize.x);
			currentQuad[1].texCoords = sf::Vector2f(0.f, 0.f);
			currentQuad[2].texCoords = sf::Vector2f(bodySize.x, 0.f);
			currentQuad[3].texCoords = sf::Vector2f(bodySize);
			break;
		case -1:
			currentQuad[0].texCoords = sf::Vector2f(0.f, 0.f);
			currentQuad[1].texCoords = sf::Vector2f(0.f, bodySize.x);
			currentQuad[2].texCoords = sf::Vector2f(bodySize);
			currentQuad[3].texCoords = sf::Vector2f(bodySize.x, 0.f);
			break;
	}

	quadPtr += 4;

	Scene::window.draw(vertexArray, renderStates);
}
