#include "ActionNode.h"
#include <random>

ActionNode::ActionNode()
		  : m_actionName("Unkown") {
}

ActionNode::ActionNode(const std::string& actionName)
		  : m_actionName(actionName) {}

NodeState ActionNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
	std::cout << "Action: " << m_actionName << std::endl;
	return NodeState::SUCCESS;
}

NodeState PatrolNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    static float distance = 0.f;
    static sf::Vector2f goTo = { -1, -1 };
    static int cooldown = 0;
    static int cooldownWhenArrived = 0;

    if (blackboard->getValue<bool>("isOnSearchCooldown") == true)
    {
        blackboard->setValue("isSearching", true);
        NodeState::FAILURE;
    }

    entity->shape.setFillColor(sf::Color::Cyan);

    std::random_device randomDevice;
    std::mt19937 seed(randomDevice());
    std::uniform_int_distribution<> randX(0, GRID_WIDTH);
    std::uniform_int_distribution<> randY(0, GRID_HEIGHT);

    sf::Vector2f targetPosition = {
        static_cast<float>(randX(seed) % GRID_WIDTH)* CELL_SIZE,
        static_cast<float>(randY(seed) % GRID_HEIGHT) * CELL_SIZE
    };

    if (goTo == sf::Vector2f{-1.f, -1.f} || cooldown >= 60*20)
    {
        cooldown = 0;
        goTo = targetPosition;
    }
   
    sf::Vector2i targetGridPosition = (sf::Vector2i)goTo / CELL_SIZE;
    sf::Vector2i entitytGridPosition = (sf::Vector2i)entity->shape.getPosition() / CELL_SIZE;

    std::cout << "Action: " << m_actionName << "\t->\t{ " << targetGridPosition.x << ", " << targetGridPosition.y << " }" << std::endl;

    auto path = entity->pathfinding.findPath(grid,
        entitytGridPosition,
        targetGridPosition);

    sf::Vector2f direction = { 0, 0 };
    if (!path.empty() && entitytGridPosition != targetGridPosition) {
        direction = { ((float)path[1].x * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().x,
                      ((float)path[1].y * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().y };
    }
    else
    {
        entity->velocity = { 0.f, 0.f };

        if (cooldownWhenArrived > stopTime * 60)
        {
            cooldown = 0;
            cooldownWhenArrived = 0;
            goTo = { -1.f, -1.f };
            return NodeState::FAILURE;
        }

        cooldownWhenArrived++;
    }

    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (!distance < 1.0f) {
        direction /= distance;
        entity->velocity += direction * speedMultiplicator;
    }
    else
    {
        entity->velocity = { 0.f, 0.f };

        if (cooldownWhenArrived > stopTime * 60)
        {
            cooldown = 0;
            cooldownWhenArrived = 0;
            goTo = { -1.f, -1.f };
        }

        cooldownWhenArrived++;
    }
    return NodeState::SUCCESS;
}


NodeState ChaseNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    static float distance = 0.f;

    entity->shape.setFillColor(sf::Color::Magenta);

	auto targetPosition = blackboard->getValue<sf::Vector2f>("GoTo");

	sf::Vector2i targetGridPosition = (sf::Vector2i)targetPosition / CELL_SIZE;
	sf::Vector2i entitytGridPosition = (sf::Vector2i)entity->shape.getPosition() / CELL_SIZE;

	std::cout << "Action: " << m_actionName << "\t->\t{ " << targetGridPosition.x << ", " << targetGridPosition.y << " }" << std::endl;

	auto path = entity->pathfinding.findPath(grid,
				entitytGridPosition,
				targetGridPosition);

    sf::Vector2f direction = { 0, 0 };
    if (!path.empty() && entitytGridPosition != targetGridPosition) {
        direction = { ((float)path[1].x * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().x,
                      ((float)path[1].y * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().y };
    }
    else
    {
        //std::cout << "INVALID PATH\n";
        //return NodeState::FAILURE;
    }

    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (!distance < 1.0f) {
        direction /= distance;
        entity->velocity += direction * speedMultiplicator;
    }

    return NodeState::SUCCESS;
}

NodeState SearchNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    static float distance = 0.f;
    static int cooldown = 0;

    entity->shape.setFillColor(sf::Color::Yellow);

    auto targetPosition = blackboard->getValue<sf::Vector2f>("GoTo");

    blackboard->setValue("isOnSearchCooldown", true);

    sf::Vector2i targetGridPosition = (sf::Vector2i)targetPosition / CELL_SIZE;
    sf::Vector2i entitytGridPosition = (sf::Vector2i)entity->shape.getPosition() / CELL_SIZE;

    std::cout << "Action: " << m_actionName << "\t->\t{ " << targetGridPosition.x << ", " << targetGridPosition.y << " }" << std::endl;

    auto path = entity->pathfinding.findPath(grid,
        entitytGridPosition,
        targetGridPosition);

    sf::Vector2f direction = { 0, 0 };
    if (!path.empty() && entitytGridPosition != targetGridPosition) {
        direction = { ((float)path[1].x * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().x,
                      ((float)path[1].y * CELL_SIZE + CELL_SIZE / 2.f) - entity->shape.getPosition().y };
    }
    else
    {
        entity->velocity = { 0.f, 0.f };

        if (cooldown > stopTime * 60)
        {
            cooldown = 0;
            blackboard->setValue("isOnSearchCooldown", false);
            blackboard->setValue("isSearching", false);
            return NodeState::FAILURE;
        }

        cooldown++;
    }

    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (!distance < 1.0f) {
        direction /= distance;
        entity->velocity += direction * speedMultiplicator;
    }
    else
    {
        entity->velocity = { 0.f, 0.f };

        if (cooldown > 25 * 60)
        {
            cooldown = 0;
            blackboard->setValue("isOnSearchCooldown", false);
            blackboard->setValue("isSearching", false);
            return NodeState::FAILURE;
        }

        cooldown++;
    }

    return NodeState::SUCCESS;
}
