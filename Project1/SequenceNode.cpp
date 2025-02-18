#include "SequenceNode.h"

void SequenceNode::addChild(std::unique_ptr<BTNode> child)
{
    m_children.push_back(std::move(child));
}

NodeState SequenceNode::execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity)
{
    for (auto& child : m_children) {
        if (child->execute(grid, blackboard, entity) == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}