#include "GOAPAgent.h"

GOAPAgent::GOAPAgent() : currentGoal(Goal::PATROL) {}

void GOAPAgent::setGoal(Goal goal)
{
	currentGoal = goal;
}

void GOAPAgent::updateState(State& state)
{
	if (state.getShouldFlee()) {
		setGoal(Goal::FLEE);
	}
	else if (state.getHunting()) {
		setGoal(Goal::HUNT);
	}
	else if (state.getSearching()) {
		setGoal(Goal::SEARCH);
	}
	else {
		setGoal(Goal::PATROL);
	}
}

void GOAPAgent::PerformActions(State& state)
{
	vector<unique_ptr<Action>> actions = planner.Plan(state, currentGoal);

	for (auto& action : actions) {
		action->Execute(state);
	}
}

void GOAPAgent::update(float deltaTime, State& state)
{
	updateState(state);
	PerformActions(state);
}
