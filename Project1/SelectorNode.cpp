#include "SelectorNode.h"

void SelectorNode::addChild(std::unique_ptr<BTNode> child)
{
    m_children.push_back(std::move(child));
}

NodeState SelectorNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    for (auto& child : m_children) {
        if (child->execute(grid, blackboard, entity) == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}