#include "SelectorNode.h"

void SelectorNode::addChild(std::unique_ptr<BTNode> child)
{
    m_children.push_back(std::move(child));
}

NodeState SelectorNode::execute()
{
    for (auto& child : m_children) {
        if (child->execute() == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}