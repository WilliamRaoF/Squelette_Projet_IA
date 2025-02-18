#include "SearchAction.h"

bool SearchAction::CanExecute(const State& state)
{
	return !state.getHunting() && !state.getPatrolling() && !state.getShouldFlee();
}

void SearchAction::Execute(State& state)
{
	cout << "L'ennemi Cherche le joueur";
	state.setSearching(true);
}
