#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "BTNode.h"

#include <memory>
#include <iostream>

class ConditionNode : public BTNode
{
public:
	ConditionNode(const std::string& key, bool value)
		: m_key(key), m_expectedValue(value)
	{}

	NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;

private:
	std::string m_key;
	bool m_expectedValue;
};

#endif