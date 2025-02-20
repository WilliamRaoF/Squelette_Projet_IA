#include "BehaviorTree.h"

BTree::BTree(Grid& grid, std::shared_ptr<Entity> attachedEntity)
{
	m_blackboard = std::make_shared<Blackboard>();
	m_root = std::make_unique<SelectorNode>();

	m_entity = attachedEntity;
	m_grid = grid;
}

BTree::BTree()
{
	m_blackboard = std::make_shared<Blackboard>();
	m_root = std::make_unique<SelectorNode>();

	m_entity = nullptr;
}

std::shared_ptr<Blackboard> BTree::getBlackboard()
{
	return m_blackboard;
}

void BTree::addChildToRoot(std::unique_ptr<BTNode> child)
{
	m_root->addChild(std::move(child));
}

void BTree::executeRoot()
{
	m_root->execute(m_grid, m_blackboard, m_entity);
}
