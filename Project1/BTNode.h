#ifndef BTNODE_H
#define BTNODE_H

#include "Blackboard.h"
#include "Entity.hpp"

enum NodeState { SUCCESS, FAILURE, RUNNING };

class BTNode
{
public:
	virtual NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) = 0;
	virtual ~BTNode() = default;
};

#endif