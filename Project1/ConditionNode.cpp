#include "ConditionNode.h"

NodeState ConditionNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    try {
        bool blackboardValue = blackboard->getValue<bool>(m_key);

        if (blackboardValue == m_expectedValue) 
        {
            return NodeState::SUCCESS;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[CONDITION NODE ERROR] : " << e.what() << std::endl;
        return NodeState::FAILURE;
    }

    return NodeState::FAILURE;
}
