#include "ActionNode.h"

ActionNode::ActionNode()
		  : m_actionName("Unkown") {
}

ActionNode::ActionNode(const std::string& actionName)
		  : m_actionName(actionName) {}

NodeState ActionNode::execute()
{
	std::cout << "Action: " << m_actionName << std::endl;
	return NodeState::SUCCESS;
}

