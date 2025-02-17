#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "BTNode.h"
#include "Blackboard.h"

#include <memory>
#include <iostream>

class ConditionNode : public BTNode
{
public:
	ConditionNode(const std::shared_ptr<Blackboard>& blackboard, const std::string& key, bool value)
		: m_blackboard(blackboard), m_key(key), m_expectedValue(value)
	{}

	NodeState execute() override;

private:
	std::shared_ptr<Blackboard> m_blackboard;
	std::string m_key;
	bool m_expectedValue;
};

#endif