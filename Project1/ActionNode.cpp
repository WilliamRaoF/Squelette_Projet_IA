#include "ActionNode.h"

ActionNode::ActionNode()
		  : m_actionName("Unkown") {
}

ActionNode::ActionNode(const std::string& actionName, const std::shared_ptr<Blackboard>& blackboard)
		  : m_actionName(actionName), m_blackboard(blackboard) {}

NodeState ActionNode::execute()
{
	std::cout << "Action: " << m_actionName << std::endl;
	return NodeState::SUCCESS;
}

NodeState ChaseNode::execute()
{
	auto goTo = m_blackboard->getValue<sf::Vector2f>("GoTo");
	std::cout << "Action: " << m_actionName << "\t->\t{ " << goTo.x << ", " << goTo.y << " }" << std::endl;
	return NodeState::SUCCESS;
}
