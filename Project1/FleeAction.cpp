#include "FleeAction.h"

bool FleeAction::CanExecute(const State& state)
{
	return !state.getPatrolling() && !state.getSearching() && !state.getHunting();
}

void FleeAction::Execute(State& state)
{
	cout << "L'ennemi fuit face au joueur";
	state.setShouldFlee(true);
}