#ifndef ACTION_NODE_H
#define ACTION_NODE_H

#include <SFML//Graphics.hpp>

#include "BTNode.h"
#include "Blackboard.h"

#include <iostream>
#include <string>

class ActionNode : public BTNode {
public:
    ActionNode();
    ActionNode(const std::string& actionName, const std::shared_ptr<Blackboard>& blackboard);
    NodeState execute() override;
protected:
    std::shared_ptr<Blackboard> m_blackboard;
    std::string m_actionName;
};

class PatrolNode : public ActionNode {
public:
    PatrolNode() { m_actionName = "Patrolling"; }
    //NodeState execute() override;
};

class ChaseNode : public ActionNode {
public:
    ChaseNode() { m_actionName = "Chase"; }
    NodeState execute() override;
};




#endif