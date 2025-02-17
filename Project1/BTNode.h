#ifndef BTNODE_H
#define BTNODE_H

enum NodeState { SUCCESS, FAILURE, RUNNING };

class BTNode
{
public:
	virtual NodeState execute() = 0;
	virtual ~BTNode() = default;
};

#endif