#include "PatrolAction.h"

bool PatrolAction::CanExecute(const State& state)
{
	return !state.getHunting() && !state.getSearching() && !state.getShouldFlee();
}

void PatrolAction::Execute(State& state)
{
	cout << "L'ennemi patrouille";
	state.setPatrolling(true);
}
