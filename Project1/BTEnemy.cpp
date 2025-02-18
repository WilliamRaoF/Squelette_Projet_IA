#include "BTEnemy.h"

BTEnemy::BTEnemy(float x, float y) : Entity(x, y, sf::Color::Cyan)
{
	shape.setOrigin(shape.getSize() / 2.f);
}

void BTEnemy::update(float deltaTime, Grid& grid)
{
	behavior->executeRoot();
}

void BTEnemy::update(float deltaTime, Grid& grid, Player& player)
{
	sf::Vector2f playerPos = player.shape.getPosition();
	sf::Vector2f pos = shape.getPosition();

	velocity = { 0, 0 };

	float distance = std::hypot(playerPos.x - pos.x, playerPos.y - pos.y);

	if (distance <= DETECTION_RADIUS)
	{
		behavior->getBlackboard()->setValue("isPlayerDetected", true);

		behavior->getBlackboard()->setValue("GoTo", playerPos);
	}
	else
	{
		behavior->getBlackboard()->setValue("isPlayerDetected", false);
	}
	behavior->executeRoot();

	shape.setPosition(pos + velocity * deltaTime * SPEED);
}

void BTEnemy::initBTree(Grid& grid)
{
	behavior = std::make_shared<BTree>(grid, shared_from_this());

	behavior->getBlackboard()->setValue("isPlayerDetected", false);
	behavior->getBlackboard()->setValue("GoTo", sf::Vector2f{ 0, 0 });

	auto plrDetect = std::make_unique<SequenceNode>();
	auto patrolling = std::make_unique<SequenceNode>();

	plrDetect->addChild(std::make_unique<ConditionNode>("isPlayerDetected", true));
	plrDetect->addChild(std::make_unique<ChaseNode>());
	patrolling->addChild(std::make_unique<PatrolNode>());

	behavior->addChildToRoot(std::move(plrDetect));
	behavior->addChildToRoot(std::move(patrolling));
}
