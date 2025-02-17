#include "SequenceNode.h"

void SequenceNode::addChild(std::unique_ptr<BTNode> child)
{
    m_children.push_back(std::move(child));
}

NodeState SequenceNode::execute()
{
    for (auto& child : m_children) {
        if (child->execute() == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}