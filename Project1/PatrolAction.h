#pragma once

#include "Action.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include "EnemyGOAP.h"

class PatrolAction : public Action {
private: 
	EnemyGOAP* enemyGoap;
public:
	bool CanExecute(const State& state) override;
	void Execute(State& state) override;
};