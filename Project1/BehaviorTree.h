#ifndef BTREE_H
#define BTREE_H

#include "Entity.hpp"
#include "Nodes.h"

class BTree
{
public:

	BTree(Grid& grid, std::shared_ptr<Entity> attachedEntity);
	BTree();

	std::shared_ptr<Blackboard> getBlackboard();

	void addChildToRoot(std::unique_ptr<BTNode> child);
	void executeRoot();

private:
	std::shared_ptr<Blackboard> m_blackboard;
	std::unique_ptr<SelectorNode> m_root;

	std::shared_ptr<Entity> m_entity;

	Grid m_grid;
};

#endif