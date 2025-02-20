#pragma once
#include "Action.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include "EnemyGOAP.h"
#include "Player.hpp"

class HuntAction : public Action {
private: 
	EnemyGOAP* enemyGoap;
	Player* player;
public:
	bool CanExecute(const State& state) override;
	void Execute(State& state) override;
};