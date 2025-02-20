#include "EnemyGOAP.h"



EnemyGOAP::EnemyGOAP(Player& p, Vector2f pos, float radiusDetect, int hp) : Enemy(pos, hp), player(p), detectionRadius(radiusDetect) 
{
    currentGoal = Goal::PATROL;
    state.setPatrolling(true);
    state.setHunting(false);
    state.setSearching(false);
    state.setShouldFlee(false);
	detectionRadius = 100.0f;
	state.healthGOAP = 100;
	state.positionGOAP = pos;
}

void EnemyGOAP::setGoal(Goal goal)
{
    currentGoal = goal;
}

void EnemyGOAP::updateState(State& state)
{

    if (state.getShouldFlee()) {
        setGoal(Goal::FLEE);
    }
    else if (state.getHunting()) {
        setGoal(Goal::HUNT);
    }
    else {
        setGoal(Goal::PATROL);
    }

    PerformActions(state);
}

void EnemyGOAP::PerformActions(State& state)
{
    vector<unique_ptr<Action>> actions = planner.Plan(state, currentGoal);

    for (auto& action : actions) {
        if (action->CanExecute(state))
        {
            action->Execute(state);
        }
    }
}


void EnemyGOAP::update(float deltaTime, Grid& grid, std::vector<Entity*> players)
{
}
