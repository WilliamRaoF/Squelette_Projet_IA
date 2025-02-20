#include "BTNode.h"

NodeState BTNode::execute()
{
    std::cout << "[UNTYPED NODE]: executed\n";
    return NodeState::SUCCESS;
}
