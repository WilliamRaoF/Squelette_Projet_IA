#include "HuntAction.h"

bool HuntAction::CanExecute(const State& state)
{
	return !state.getPatrolling() && !state.getSearching() && !state.getShouldFlee();
}

void HuntAction::Execute(State& state)
{
	cout << "L'ennemi chasse le joueur";
	state.setHunting(true);
}