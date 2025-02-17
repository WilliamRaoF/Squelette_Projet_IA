#ifndef BTREE_H
#define BTREE_H

#include "Nodes.h"

class BTree
{
public:

	BTree();

	std::shared_ptr<Blackboard> getBlackboard();

	void addChildToRoot(std::unique_ptr<BTNode> child);
	void executeRoot();

private:
	std::shared_ptr<Blackboard> m_blackboard;
	std::unique_ptr<SelectorNode> m_root;
};

#endif