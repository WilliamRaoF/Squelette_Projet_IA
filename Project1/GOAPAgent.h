#pragma once

#include <iostream>
#include <memory>

#include "State.h"
#include "GOAPPlanner.h"


class GOAPAgent {
private: 
	Goal currentGoal;
	GOAPPlanner planner;

public:
	GOAPAgent();
	void setGoal(Goal goal);
	void updateState(State& state);
	void PerformActions(State& state);
	void update(float deltaTime, State& state);
};
