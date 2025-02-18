#ifndef SELECTOR_NODE_H
#define SELECTOR_NODE_H

#include "BTNode.h"

#include <vector>
#include <memory>

class SelectorNode : public BTNode
{
public:
	void addChild(std::unique_ptr<BTNode> child);
	NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;

private:
	std::vector<std::unique_ptr<BTNode>> m_children;
};

#endif