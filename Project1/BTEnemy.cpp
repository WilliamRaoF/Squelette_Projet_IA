#include "BTEnemy.h"

BTEnemy::BTEnemy(float x, float y) : Entity(x, y, sf::Color::Cyan)
{
	//setup tree

	behavior.getBlackboard()->setValue("isPlayerDetected", false);

	auto plrDetect = std::make_unique<SequenceNode>();
	auto patrolling = std::make_unique<SequenceNode>();

	plrDetect->addChild(std::make_unique<ConditionNode>(behavior.getBlackboard(), "isPlayerDetected", true));
	plrDetect->addChild(std::make_unique<ChaseNode>());
	patrolling->addChild(std::make_unique<PatrolNode>());

	behavior.addChildToRoot(std::move(plrDetect));
	behavior.addChildToRoot(std::move(patrolling));
}

void BTEnemy::update(float deltaTime, Grid& grid)
{
	behavior.executeRoot();
}

void BTEnemy::update(float deltaTime, Grid& grid, Player& player)
{
	sf::Vector2f playerPos = player.shape.getPosition();
	sf::Vector2f pos = shape.getPosition();

	float distance = std::hypot(playerPos.x - pos.x, playerPos.y - pos.y);

	if (distance <= 150.f)
	{
		behavior.getBlackboard()->setValue("isPlayerDetected", true);
		behavior.getBlackboard()->setValue("GoTo", playerPos);
	}
	else
	{
		behavior.getBlackboard()->setValue("isPlayerDetected", false);
	}
	behavior.executeRoot();
}
